#ifndef _ATLAS_H
#define _ATLAS_H

#include <glm/common.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <logger.h>

#include <cstdlib>
#include <cstdint>

namespace cellwars
{
    typedef uint8_t byte;

    /*! @brief Handles font loading
     *
     *  Should not be used in 99% of the times. It's purpose is to
     *  lay the ground for the font class.
     *
     *  This class will source a font via freetype2. It will then store
     *  two pointers to represent glyphs. First, the atlas texture,
     *  accessible via @ref get_ctex, then the metadata, which is
     *  an arrau of @ref gslot. Characters between ASCII 32 and
     *  126 will be stored. To access the slot properties of a
     *  given character, do something like this: get_cmeta()[c - ''].
     */
    class atlas
    {
    public:
        /*! @brief Describes information stored in @ref get_cmeta
         */
        struct gslot
        {
            /*! @brief Top-left corner of slot (in px).
             */
            glm::ivec2 lefttop;

            /*! @brief Size of slot (in px).
             */
            glm::uvec2 size;

            /*! @brief Advance to next slot (in px).
             */
            uint32_t advance;
        };

    public:
        /*! @brief Default ctor
         *
         *  As a type-safe measure, the pointers will be initialized to null.
         */
        atlas ()
        {
            tex = nullptr;
            metadata = nullptr;
        }

        /*! @brief No copy ctor
         *
         *  To implement copy ctors properly, one must introcude additional overhead (like smart pointers).
         *  Since it also includes code complexity, it is best avoided.
         */
        atlas (const atlas&) = delete;

        /*! @brief Move ctor
         *
         *  Change ownership of the loaded atlas.
         */
        atlas (atlas&& rhs)
        {
            this->tex = rhs.tex;
            this->metadata = rhs.metadata;

            rhs.tex = nullptr;
            rhs.metadata = nullptr;
        }

        /*! @brief Conveniently change ownership of atlas.
         *
         *  @remark Does not return (*this)
         */
        void operator= (atlas&& rhs)
        {
            this->tex = rhs.tex;
            this->metadata = rhs.metadata;

            rhs.tex = nullptr;
            rhs.metadata = nullptr;
        }

        /*! @brief Destructor.
         *
         *  Performes cleanup as promised when object goes out-of-scope.
         */
        ~atlas ()
        {
            std::free (tex);
            std::free (metadata);
        }

        /*! @brief Load atlas from disk
         *
         *  @param path Path to file on file system.
         *  @param dpi_horz Horizontal dpi of monitor.
         *  @param dpi_vert Vertical dpi of monitor.
         *  @param h_size Horizontal point size for atlas.
         *  @return True/false on success/failure respectively.
         */
        bool load (const char* path, float dpi_horz, float dpi_vert, float h_size)
        {
            bool retval = impl_load (path, dpi_horz, dpi_vert, h_size);
            if (!retval)
            {
                free ();
            }

            return retval;
        }

        /*! @brief Check if loading the atlas succeeded.
         *
         *  @remark If @ref load has not been called, then this function will return false.
         */
        bool is_loaded () const
        {
            return tex != nullptr && metadata != nullptr;
        }

        /*! @brief Release resources early (before going out-of-scope)
         */
        void free ()
        {
            free_tex ();
            free_meta ();
        }

        /*! @brief Release texture information only
         */
        void free_tex ()
        {
            std::free (tex);
            tex = nullptr;
        }

        /*! @brief Release metadata information only
         */
        void free_meta ()
        {
            std::free (metadata);
            metadata = nullptr;
        }

        /*! @brief Get pointer to texture
         *
         *  @remark Cannot modify data (ro accces).
         */
        const byte* get_ctex () const
        {
            return tex;
        }

        /*! @brief Get pointer to metadata
         *
         *  @remark Cannot modify data (ro accces).
         */
        const gslot* get_cmeta () const
        {
            return metadata;
        }

    private:
        bool impl_load (const char* path, float dpi_horz, float dpi_vert, float h_size)
        {
            FT_Library ft;
            FT_Error s;

            s = FT_Init_FreeType (&ft);
            if (s != 0)
            {
                logError ("failed initializing freetype; error code: %d", s);
                return false;
            }

            FT_Face face;
            s = FT_New_Face (ft, path, 0, &face);

            if (s != 0)
            {
                logError ("failed to open %s; error code: %d", path, s);
                return false;
            }

            s = FT_Set_Char_Size (face, 0, h_size * 64, dpi_horz, dpi_vert);
            if (s != 0)
            {
                logError ("FT_Set_Char_Size failed; error code is %d", s);
                return false;
            }

            unsigned max_glypth_width = (face->bbox.xMax - face->bbox.xMin) / 64;
            unsigned max_glypth_height = (face->bbox.yMax - face->bbox.yMin) / 64;

            if (max_glypth_width > 60 || max_glypth_height > 60)
            {
                logError ("unusually high dpi (%lf, %lf), glyph size should be higher than 64x64", dpi_horz, dpi_vert);
                logError ("required size: %ux%u", max_glypth_width, max_glypth_height);
                return false;
            }

            metadata = (gslot*)malloc (sizeof (gslot) * num_glyphs);
            if (metadata == nullptr)
            {
                logError ("malloc(3) returned NULL");
                return false;
            }

            tex = (byte*)calloc (sizeof (byte), 1024 * 1024);
            if (tex == nullptr)
            {
                logError ("calloc(3) returned NULL");
                return false;
            }

            for (char c = ' '; c <= '~'; ++c)
            {
                unsigned id = c - ' ';

                s = FT_Load_Char (face, c, FT_LOAD_RENDER);
                if (s != 0)
                {
                    logError ("failed loading \'%c\'; error code: %d", c, s);
                    return false;
                }

                if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
                {
                    s = FT_Render_Glyph (face->glyph, FT_RENDER_MODE_NORMAL);
                    if (s != 0)
                    {
                        logError ("FT_Render_Glyph failed for \'%c\'; error code: %d", c, s);
                        return false;
                    }
                }

                FT_GlyphSlot glyph = face->glyph;

                metadata[id].size = glm::uvec2 (glyph->bitmap.width, glyph->bitmap.rows);
                metadata[id].lefttop = glm::ivec2 (glyph->bitmap_left, glyph->bitmap_top);
                metadata[id].advance = glyph->advance.x / 64;

                unsigned s = id % 16;
                unsigned t = id / 16;
                byte* start = tex + (1024 * 64 * t + s * 64);

                if (glyph->bitmap.pitch > 0)
                {
                    for (unsigned row = 0; row < glyph->bitmap.rows; ++row)
                    {
                        unsigned offset = (glyph->bitmap.rows - row - 1) * glyph->bitmap.pitch;
                        memcpy (start + row * 1024, glyph->bitmap.buffer + offset, glyph->bitmap.pitch);
                    }
                }
                else
                {
                    for (unsigned row = 0; row < glyph->bitmap.rows; ++row)
                    {
                        unsigned offset = row * -(glyph->bitmap.pitch);
                        memcpy (start + row * 1024, glyph->bitmap.buffer + offset, -(glyph->bitmap.pitch));
                    }
                }
            }

            s = FT_Done_Face (face);
            if (s != 0)
            {
                logWarn ("failed closing face %s, ignoring...", path);
            }

            s = FT_Done_FreeType (ft);
            if (s != 0)
            {
                logWarn ("failed closing freetype library handler, ignoring...");
            }

            return true;
        }

    public:
        /*! @brief Total number of glyphs loaded/.
         */
        static constexpr unsigned num_glyphs = 95;

    private:
        byte* tex;
        gslot* metadata;
    };
};

#endif /* _ATLAS_H */

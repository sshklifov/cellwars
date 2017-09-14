#ifndef RENDER_CIRCLE_INCLUDED
#define RENDER_CIRCLE_INCLUDED

#include <Epsilon/Circle.h>
#include <RenderUtils/ArrayObjects.h>
#include <RenderUtils/Program.h>
#include <Container/Vector.h>
#include <Container/String.h>
#include <Misc/LocalPtr.h>

namespace Cellwars
{
    class RenderGeometry
    {
    public:
        virtual ~RenderGeometry () {}
        virtual void Render () = 0;
        virtual float Priority () const = 0;
        virtual bool Identify (const char* s) const = 0;
    };

    class RenderCircle : public RenderGeometry
    {
    private:
        enum {VBO_CIRCLE, VBO_CNT};
        enum {VAO_CIRCLE, VAO_CNT};

        struct VertexShaderData
        {
            FVec3 colour;
            FPoint2 center;
            float rad;
        };

    public:
        RenderCircle (const FCircle& c, const FVec3& colour, const char* name);
        virtual void Render () override;
        virtual bool Identify (const char* s) const override;
        virtual float Priority () const override;

        float GetRad () const;
        void SetRad (float rad);
        const FPoint2& GetCenter () const;
        void SetCenter (const FPoint2& center);
        const FVec3& GetColour () const;
        void SetColour (const FVec3& colour);
        const char* GetName () const;
        void SetName (const char* s);

    private:
        FCircle c;
        FVec3 colour;
        String name;

        VboArray<VBO_CNT> vbo;
        VaoArray<VAO_CNT> vao;
        Program prog;

    public:
        static constexpr unsigned max_circles = 100;
        static constexpr char string_id[] = "circle";
    };

    class RenderBlob : public RenderGeometry
    {
    private:
        enum {VBO_BLOB, VBO_CNT};
        enum {VAO_BLOB, VAO_CNT};

        struct VertexShaderData
        {
            FVec3 colour;
            FPoint2 pos;
            float rad;
        };

    public:
        RenderBlob (const FPoint2& pos, const FVec3& colour);
        virtual void Render () override;
        virtual bool Identify (const char* s) const override;
        virtual float Priority () const override;

        const FPoint2& GetPos () const;
        void SetPos (const FPoint2& center);
        const FVec3& GetColour () const;
        void SetColour (const FVec3& colour);

    private:
        FPoint2 pos;
        FVec3 colour;

        VboArray<VBO_CNT> vbo;
        VaoArray<VAO_CNT> vao;
        Program prog;

    public:
        static constexpr unsigned max_blobs = 500;
        static constexpr char string_id[] = "blob";
        static constexpr unsigned blob_rad = 20.f;
    };

    class RenderLines : public RenderGeometry
    {
    private:
        enum {VBO_LINES, VBO_CNT};
        enum {VAO_LINES, VAO_CNT};

    public:
        RenderLines ();

        virtual void Render () override;
        virtual bool Identify (const char* s) const override;
        virtual float Priority () const override;

    private:
        VboArray<VBO_CNT> vbo;
        VaoArray<VAO_CNT> vao;
        Program prog;

    public:
        static constexpr float line_spacing = 100;
        static constexpr float min_line_spacing = 25;
        static constexpr char string_id[] = "lines";
    };

    class RenderGeometryContainer
    {
    public:
        class Singleton;
        static Singleton& GetInstance ();

    public:
        static RenderCircle* GetPlayer ();
        static RenderCircle* p_player;
    };

    class RenderGeometryContainer::Singleton
    {
    public:
        Singleton () = default;
        ~Singleton ();

        void PushBack (NewPtr<RenderGeometry> p);
        void Remove (unsigned idx);
        void Remove (RenderGeometry* ptr);
        unsigned Size () const;
        void Render ();
        void Sort ();

        RenderGeometry* operator[] (unsigned idx);

        template <typename T>
        T* GetGeometry (unsigned idx);

        template <typename T>
        const T* GetGeometry (unsigned idx) const;

    private:
        Vector<RenderGeometry*> v;
    };
};

#include "RenderGeometryContainer.inl"

#endif /* RENDER_CIRCLE_INCLUDED */

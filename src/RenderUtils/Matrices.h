#ifndef MATRICES_INCLUDED
#define MATRICES_INCLUDED

/*! @file Matrices.h
 *
 *  Since there are going to be a lot of programmes that would need to access 
 *  transformation matrices, i.e. projection, scale, translate and mvp for
 *  the combined transformations, this class will be in charge of updating
 *  and storing them. A UBO will be used for this matter, and the defualt
 *  binding point of 0 will be used.
 */

#include <glad/glad.h>
#include <glm/matrix.hpp>

namespace Cellwars
{
    class Matrices
    {
    public:
        class Singleton;
        static Singleton& GetInstance ();

        static void RegisterProgram (GLuint prog);

    public:
        static constexpr unsigned binding_point = 0;
        static constexpr char block_name[] = "matrices";
    };

    class Matrices::Singleton
    {
    public:
        Singleton ();
        ~Singleton ();

        Singleton (const Singleton&) = delete;
        Singleton (Singleton&&) = delete;
        void operator= (const Singleton&) = delete;
        void operator= (Singleton&&) = delete;

        const glm::mat4& GetProjectionMatrix () const;
        const glm::mat4& GetScaleMatrix () const;
        const glm::mat4& GetTranslateMatrix () const;

        void SetProjectionMatrix (const glm::mat4& m);
        void SetScaleMatrix (const glm::mat4& m);
        void SetTranslateMatrix (const glm::mat4& m);

        bool IsLoaded () const;
        void CoherentUpdate ();

    private:
        void UpdateScaleIfSet (float* buf);
        void UpdateProjectionIfSet (float* buf);
        void UpdateTranslateIfSet (float* buf);
        void UpdateMvpIfSet (float* buf);
        void UpdateMatrixIfSet (int matrix, void* buf, void* data);

    private:
        GLuint ubo;
        glm::mat4 projection;
        glm::mat4 scale;
        glm::mat4 translate;
        int update_bitfield;

    private:
        enum {SCALE = 1, PROJECTION = 2, TRANSLATE = 4, MVP = 8};
        static constexpr unsigned matrix_total = 4;
        static constexpr unsigned matrix_sizeof = sizeof (float[16]);
    };
};

#endif /* MATRICES_INCLUDED */

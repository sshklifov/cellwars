/* NOTE: has to be first preprocessor directive
 */
#include "../utils/utils.h"

#ifndef _RENDER_HANDLE_H
#define _RENDER_HANDLE_H

namespace cellwars
{
    /*! @brief Used for rendering stuff.
     *
     *  Responsible for the GUI part of the project. It has three distinct logical states:
     *  1) Initialize
     *  2) Login screen
     *  3) Main rendering loop
     *
     *  Every one is accessible through the class's member functions.
     */
    class render_handle
    {
    public:
        /*! @brief Default ctor
         */
        render_handle () = default;

        /*! @brief No copy ctor
         *  
         *  There will be only one instance of the rendering handle. There will
         *  be absolutely no need to call a copy ctor. See src/main.cpp.
         */
        render_handle (const render_handle&) = delete;

        /*! @brief No move ctor
         *
         *  There will be only one instance of the rendering handle. There will
         *  be absolutely no need to call a move ctor. See src/main.cpp.
         */
        render_handle (render_handle&&) = delete;

        /*! @brief Perform initialization.
         *
         *  The implementation is not inside the header. You can check it out
         *  here: src/stage_init.cpp
         *
         *  @return True/false on success/failure.
         */
        bool init ();

        /*! @brief Perform login.
         *
         *  The implementation is not inside the header. You can check it out
         *  here: src/stage_login.cpp
         *
         *  @return True/false on success/failure.
         */
        bool login ();

        /*! @brief Perform main rendering loop.
         *
         *  The implementation is not inside the header. You can check it out
         *  here: src/stage_main.cpp
         *
         *  @return True/false on success/failure.
         */
        bool main ();

    private:
        cellwars::window window;
        cellwars::font font;
        unsigned width;
        unsigned height;
    };
};

#endif /* _RENDER_HANDLE_H */

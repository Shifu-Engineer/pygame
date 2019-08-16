/*
    pygame - Python Game Library
    Copyright (C) 2000-2001  Pete Shinners

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Pete Shinners
    pete@shinners.org
*/
#define NO_PYGAME_C_API
#include "pygame.h"

#include "pgcompat.h"

#include "scrap.h"

/* macros used to create each constant */
#if IS_SDLv2
#define ADD_ERROR           \
    {                       \
        DECREF_MOD(module); \
        MODINIT_ERROR;      \
    }
#define STRINGIZE(x) #x
#define DEC_CONSTS_(x, y)                           \
    if (PyModule_AddIntConstant(module, x, (int)y)) \
    ADD_ERROR
#define DEC_CONSTS(x, y) DEC_CONSTS_(#x, y)
#define DEC_CONST(x) DEC_CONSTS_(#x, SDL_##x)
#define DEC_CONSTKS(x, y) DEC_CONSTS_(STRINGIZE(K_##x), SDLK_##y)
#define DEC_CONSTK(x) DEC_CONSTS_(STRINGIZE(K_##x), SDLK_##x)
#define DEC_CONSTSCS(x, y) DEC_CONSTS_(STRINGIZE(KSCAN_##x), SDL_SCANCODE_##y)
#define DEC_CONSTSC(x) DEC_CONSTS_(STRINGIZE(KSCAN_##x), SDL_SCANCODE_##x)
#define DEC_CONSTKS_AND_SCS(x, y)                        \
    DEC_CONSTS_(STRINGIZE(K_##x), SDLK_##y)              \
    DEC_CONSTS_(STRINGIZE(KSCAN_##x), SDL_SCANCODE_##y)
#define DEC_CONSTK_AND_SC(x)                           \
    DEC_CONSTS_(STRINGIZE(K_##x), SDLK_##x)            \
    DEC_CONSTS_(STRINGIZE(KSCAN_##x), SDL_SCANCODE_##x)
#define DEC_CONSTN(x) DEC_CONSTS_(#x, x)
#define DEC_CONSTSF(x) DEC_CONSTS_(#x, PGS_##x)

#else /* IS_SDLv1 */
#define ADD_ERROR           \
    {                       \
        DECREF_MOD(module); \
        MODINIT_ERROR;      \
    }
#define DEC_CONST(x)                                       \
    if (PyModule_AddIntConstant(module, #x, (int)SDL_##x)) \
    ADD_ERROR
#define DEC_CONSTK(x)                                     \
    if (PyModule_AddIntConstant(module, #x, (int)SDL##x)) \
    ADD_ERROR
#define DEC_CONSTN(x)                                \
    if (PyModule_AddIntConstant(module, #x, (int)x)) \
    ADD_ERROR
#define DEC_CONSTS(x, y)                             \
    if (PyModule_AddIntConstant(module, #x, (int)y)) \
    ADD_ERROR

#endif /* IS_SDLv1 */

#define ADD_STRING_CONST(x)                        \
    if (PyModule_AddStringConstant(module, #x, x)) \
    ADD_ERROR

static PyMethodDef _constant_methods[] = {{NULL}};

/*DOC*/ static char _constants_doc[] =
    /*DOC*/ "Constants defined by SDL and needed in Pygame.\n";

MODINIT_DEFINE(constants)
{
    PyObject *module;

#if PY3
    static struct PyModuleDef _module = {PyModuleDef_HEAD_INIT,
                                         "constants",
                                         _constants_doc,
                                         -1,
                                         _constant_methods,
                                         NULL,
                                         NULL,
                                         NULL,
                                         NULL};
#endif

#if PY3
    module = PyModule_Create(&_module);
#else
    module = Py_InitModule3(MODPREFIX "constants", _constant_methods,
                            _constants_doc);
#endif
    if (module == NULL) {
        MODINIT_ERROR;
    }

    DEC_CONST(LIL_ENDIAN);
    DEC_CONST(BIG_ENDIAN);

#if IS_SDLv1
    DEC_CONST(YV12_OVERLAY);
    DEC_CONST(IYUV_OVERLAY);
    DEC_CONST(YUY2_OVERLAY);
    DEC_CONST(UYVY_OVERLAY);
    DEC_CONST(YVYU_OVERLAY);

    DEC_CONST(SWSURFACE);
    DEC_CONST(HWSURFACE);
    DEC_CONST(RESIZABLE);
    DEC_CONST(ASYNCBLIT);
    DEC_CONST(OPENGL);
    DEC_CONST(OPENGLBLIT);
    DEC_CONST(ANYFORMAT);
    DEC_CONST(HWPALETTE);
    DEC_CONST(DOUBLEBUF);
    DEC_CONST(FULLSCREEN);
    DEC_CONST(HWACCEL);
    DEC_CONST(SRCCOLORKEY);
    DEC_CONST(RLEACCELOK);
    DEC_CONST(RLEACCEL);
    DEC_CONST(SRCALPHA);
    DEC_CONST(PREALLOC);
    DEC_CONST(NOFRAME);
#else  /* IS_SDLv2 */
    DEC_CONSTSF(SWSURFACE);
    DEC_CONSTSF(HWSURFACE);
    DEC_CONSTSF(RESIZABLE);
    DEC_CONSTSF(ASYNCBLIT);
    DEC_CONSTSF(OPENGL);
    DEC_CONSTSF(OPENGLBLIT);
    DEC_CONSTSF(ANYFORMAT);
    DEC_CONSTSF(HWPALETTE);
    DEC_CONSTSF(DOUBLEBUF);
    DEC_CONSTSF(FULLSCREEN);
    DEC_CONSTSF(HWACCEL);
    DEC_CONSTSF(SRCCOLORKEY);
    DEC_CONSTSF(RLEACCELOK);
    DEC_CONSTSF(RLEACCEL);
    DEC_CONSTSF(SRCALPHA);
    DEC_CONSTSF(PREALLOC);
    DEC_CONSTSF(NOFRAME);
    DEC_CONSTSF(SHOWN);
    DEC_CONSTSF(HIDDEN);
#endif /* IS_SDLv2 */


#if IS_SDLv1
    DEC_CONSTS(SCALED, 0);
#else
    DEC_CONSTSF(SCALED);
#endif /* IS_SDLv2 */


    DEC_CONST(GL_RED_SIZE);
    DEC_CONST(GL_GREEN_SIZE);
    DEC_CONST(GL_BLUE_SIZE);
    DEC_CONST(GL_ALPHA_SIZE);
    DEC_CONST(GL_BUFFER_SIZE);
    DEC_CONST(GL_DOUBLEBUFFER);
    DEC_CONST(GL_DEPTH_SIZE);
    DEC_CONST(GL_STENCIL_SIZE);
    DEC_CONST(GL_ACCUM_RED_SIZE);
    DEC_CONST(GL_ACCUM_GREEN_SIZE);
    DEC_CONST(GL_ACCUM_BLUE_SIZE);
    DEC_CONST(GL_ACCUM_ALPHA_SIZE);
#if IS_SDLv2
    DEC_CONST(GL_ACCELERATED_VISUAL);
    DEC_CONST(GL_CONTEXT_MAJOR_VERSION);
    DEC_CONST(GL_CONTEXT_MINOR_VERSION);
    DEC_CONST(GL_SHARE_WITH_CURRENT_CONTEXT);

    DEC_CONST(GL_CONTEXT_FLAGS);
    /* context flag values: */
    DEC_CONST(GL_CONTEXT_DEBUG_FLAG);
    DEC_CONST(GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    DEC_CONST(GL_CONTEXT_ROBUST_ACCESS_FLAG);
    DEC_CONST(GL_CONTEXT_RESET_ISOLATION_FLAG);

    DEC_CONST(GL_CONTEXT_PROFILE_MASK);
    /* values for GL_CONTEXT_PROFILE_MASK: */
    DEC_CONST(GL_CONTEXT_PROFILE_CORE);
    DEC_CONST(GL_CONTEXT_PROFILE_COMPATIBILITY);
    DEC_CONST(GL_CONTEXT_PROFILE_ES);
#if SDL_VERSION_ATLEAST(2, 0, 1)
    DEC_CONST(GL_FRAMEBUFFER_SRGB_CAPABLE);
#endif
#if SDL_VERSION_ATLEAST(2, 0, 4)
    DEC_CONST(GL_CONTEXT_RELEASE_BEHAVIOR);
    /* values for GL_CONTEXT_RELEASE_BEHAVIOR: */
    DEC_CONST(GL_CONTEXT_RELEASE_BEHAVIOR_NONE);
    DEC_CONST(GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH);
#endif
#endif /* IS_SDLv2 */

#if IS_SDLv2
    DEC_CONST(BLENDMODE_NONE);
    DEC_CONST(BLENDMODE_BLEND);
    DEC_CONST(BLENDMODE_ADD);
    DEC_CONST(BLENDMODE_MOD);

#endif /* IS_SDLv2 */
#if SDL_VERSION_ATLEAST(1, 2, 5)
    DEC_CONST(GL_STEREO);
#else
    PyModule_AddIntConstant(module, "GL_STEREO", -1);
#endif

#if SDL_VERSION_ATLEAST(1, 2, 6)
    DEC_CONST(GL_MULTISAMPLEBUFFERS);
    DEC_CONST(GL_MULTISAMPLESAMPLES);
#else
    PyModule_AddIntConstant(module, "GL_MULTISAMPLEBUFFERS", -1);
    PyModule_AddIntConstant(module, "GL_MULTISAMPLESAMPLES", -1);
#endif

#if SDL_VERSION_ATLEAST(1, 2, 10)
    DEC_CONST(GL_SWAP_CONTROL);
    DEC_CONST(GL_ACCELERATED_VISUAL);
#else
    PyModule_AddIntConstant(module, "GL_SWAP_CONTROL", -1);
    PyModule_AddIntConstant(module, "GL_ACCELERATED_VISUAL", -1);
#endif

    DEC_CONSTN(TIMER_RESOLUTION);

    DEC_CONSTN(AUDIO_U8);
    DEC_CONSTN(AUDIO_S8);
    DEC_CONSTN(AUDIO_U16LSB);
    DEC_CONSTN(AUDIO_S16LSB);
    DEC_CONSTN(AUDIO_U16MSB);
    DEC_CONSTN(AUDIO_S16MSB);
    DEC_CONSTN(AUDIO_U16);
    DEC_CONSTN(AUDIO_S16);
    DEC_CONSTN(AUDIO_U16SYS);
    DEC_CONSTN(AUDIO_S16SYS);

#define SCRAP_TEXT PYGAME_SCRAP_TEXT
#define SCRAP_BMP PYGAME_SCRAP_BMP
#define SCRAP_PPM PYGAME_SCRAP_PPM
#define SCRAP_PBM PYGAME_SCRAP_PBM

    ADD_STRING_CONST(SCRAP_TEXT);
    ADD_STRING_CONST(SCRAP_BMP);
    ADD_STRING_CONST(SCRAP_PPM);
    ADD_STRING_CONST(SCRAP_PBM);
    PyModule_AddIntConstant(module, "SCRAP_CLIPBOARD", 0);
    PyModule_AddIntConstant(module, "SCRAP_SELECTION", 1);

/* BLEND_ADD is an alias for BLEND_RGB_ADD
 */
#define PYGAME_BLEND_RGB_ADD 0x1
#define PYGAME_BLEND_RGB_SUB 0x2
#define PYGAME_BLEND_RGB_MULT 0x3
#define PYGAME_BLEND_RGB_MIN 0x4
#define PYGAME_BLEND_RGB_MAX 0x5

#define PYGAME_BLEND_ADD PYGAME_BLEND_RGB_ADD
#define PYGAME_BLEND_SUB PYGAME_BLEND_RGB_SUB
#define PYGAME_BLEND_MULT PYGAME_BLEND_RGB_MULT
#define PYGAME_BLEND_MIN PYGAME_BLEND_RGB_MIN
#define PYGAME_BLEND_MAX PYGAME_BLEND_RGB_MAX

#define PYGAME_BLEND_RGBA_ADD 0x6
#define PYGAME_BLEND_RGBA_SUB 0x7
#define PYGAME_BLEND_RGBA_MULT 0x8
#define PYGAME_BLEND_RGBA_MIN 0x9
#define PYGAME_BLEND_RGBA_MAX 0x10

#define PYGAME_BLEND_PREMULTIPLIED 0x11

    DEC_CONSTS(BLEND_ADD, PYGAME_BLEND_ADD);
    DEC_CONSTS(BLEND_SUB, PYGAME_BLEND_SUB);
    DEC_CONSTS(BLEND_MULT, PYGAME_BLEND_MULT);
    DEC_CONSTS(BLEND_MIN, PYGAME_BLEND_MIN);
    DEC_CONSTS(BLEND_MAX, PYGAME_BLEND_MAX);

    DEC_CONSTS(BLEND_RGB_ADD, PYGAME_BLEND_RGB_ADD);
    DEC_CONSTS(BLEND_RGB_SUB, PYGAME_BLEND_RGB_SUB);
    DEC_CONSTS(BLEND_RGB_MULT, PYGAME_BLEND_RGB_MULT);
    DEC_CONSTS(BLEND_RGB_MIN, PYGAME_BLEND_RGB_MIN);
    DEC_CONSTS(BLEND_RGB_MAX, PYGAME_BLEND_RGB_MAX);

    DEC_CONSTS(BLEND_RGBA_ADD, PYGAME_BLEND_RGBA_ADD);
    DEC_CONSTS(BLEND_RGBA_SUB, PYGAME_BLEND_RGBA_SUB);
    DEC_CONSTS(BLEND_RGBA_MULT, PYGAME_BLEND_RGBA_MULT);
    DEC_CONSTS(BLEND_RGBA_MIN, PYGAME_BLEND_RGBA_MIN);
    DEC_CONSTS(BLEND_RGBA_MAX, PYGAME_BLEND_RGBA_MAX);
    DEC_CONSTS(BLEND_PREMULTIPLIED, PYGAME_BLEND_PREMULTIPLIED);

    /* Event types
     */
    DEC_CONST(NOEVENT);
    DEC_CONST(ACTIVEEVENT);
    DEC_CONST(KEYDOWN);
    DEC_CONST(KEYUP);
    DEC_CONST(MOUSEMOTION);
    DEC_CONST(MOUSEBUTTONDOWN);
    DEC_CONST(MOUSEBUTTONUP);
    DEC_CONST(JOYAXISMOTION);
    DEC_CONST(JOYBALLMOTION);
    DEC_CONST(JOYHATMOTION);
    DEC_CONST(JOYBUTTONDOWN);
    DEC_CONST(JOYBUTTONUP);
    DEC_CONST(VIDEORESIZE);
    DEC_CONST(VIDEOEXPOSE);
    DEC_CONST(QUIT);
    DEC_CONST(SYSWMEVENT);
    //DEC_CONST(USEREVENT);
    DEC_CONSTS(USEREVENT, PGE_USEREVENT);
    DEC_CONST(NUMEVENTS);

    DEC_CONST(HAT_CENTERED);
    DEC_CONST(HAT_UP);
    DEC_CONST(HAT_RIGHTUP);
    DEC_CONST(HAT_RIGHT);
    DEC_CONST(HAT_RIGHTDOWN);
    DEC_CONST(HAT_DOWN);
    DEC_CONST(HAT_LEFTDOWN);
    DEC_CONST(HAT_LEFT);
    DEC_CONST(HAT_LEFTUP);

    DEC_CONST(BUTTON_LEFT);
    DEC_CONST(BUTTON_MIDDLE);
    DEC_CONST(BUTTON_RIGHT);

#if IS_SDLv2
    DEC_CONST(FINGERMOTION);
    DEC_CONST(FINGERDOWN);
    DEC_CONST(FINGERUP);
    DEC_CONST(MULTIGESTURE);
    DEC_CONST(AUDIODEVICEADDED);
    DEC_CONST(AUDIODEVICEREMOVED);
    DEC_CONST(MOUSEWHEEL);
    DEC_CONST(TEXTINPUT);
    DEC_CONST(TEXTEDITING);
    DEC_CONST(WINDOWEVENT);
    DEC_CONST(WINDOWEVENT_CLOSE);

    DEC_CONST(CONTROLLERAXISMOTION);
    DEC_CONST(CONTROLLERBUTTONDOWN);
    DEC_CONST(CONTROLLERBUTTONUP);
    DEC_CONST(CONTROLLERDEVICEADDED);
    DEC_CONST(CONTROLLERDEVICEREMOVED);
    DEC_CONST(CONTROLLERDEVICEREMAPPED);

    DEC_CONSTS(BUTTON_X1, PGM_BUTTON_X1);
    DEC_CONSTS(BUTTON_X2, PGM_BUTTON_X2);
    //Still to be decided
    DEC_CONSTS(BUTTON_WHEELUP, PGM_BUTTON_WHEELUP);
    DEC_CONSTS(BUTTON_WHEELDOWN, PGM_BUTTON_WHEELDOWN);
    DEC_CONST(AUDIO_ALLOW_FREQUENCY_CHANGE);
    DEC_CONST(AUDIO_ALLOW_FORMAT_CHANGE);
    DEC_CONST(AUDIO_ALLOW_CHANNELS_CHANGE);
    DEC_CONST(AUDIO_ALLOW_ANY_CHANGE);
    DEC_CONST(DROPFILE);
    #if SDL_VERSION_ATLEAST(2, 0, 5)
        DEC_CONST(DROPTEXT);
        DEC_CONST(DROPBEGIN);
        DEC_CONST(DROPCOMPLETE);
    #else
        DEC_CONSTS(DROPTEXT, -1);
        DEC_CONSTS(DROPBEGIN, -1);
        DEC_CONSTS(DROPCOMPLETE, -1);
    #endif

    DEC_CONST(CONTROLLER_AXIS_INVALID);
    DEC_CONST(CONTROLLER_AXIS_LEFTX);
    DEC_CONST(CONTROLLER_AXIS_LEFTY);
    DEC_CONST(CONTROLLER_AXIS_RIGHTX);
    DEC_CONST(CONTROLLER_AXIS_RIGHTY);
    DEC_CONST(CONTROLLER_AXIS_TRIGGERLEFT);
    DEC_CONST(CONTROLLER_AXIS_TRIGGERRIGHT);
    DEC_CONST(CONTROLLER_AXIS_MAX);
    DEC_CONST(CONTROLLER_BUTTON_INVALID);
    DEC_CONST(CONTROLLER_BUTTON_A);
    DEC_CONST(CONTROLLER_BUTTON_B);
    DEC_CONST(CONTROLLER_BUTTON_X);
    DEC_CONST(CONTROLLER_BUTTON_Y);
    DEC_CONST(CONTROLLER_BUTTON_BACK);
    DEC_CONST(CONTROLLER_BUTTON_GUIDE);
    DEC_CONST(CONTROLLER_BUTTON_START);
    DEC_CONST(CONTROLLER_BUTTON_LEFTSTICK);
    DEC_CONST(CONTROLLER_BUTTON_RIGHTSTICK);
    DEC_CONST(CONTROLLER_BUTTON_LEFTSHOULDER);
    DEC_CONST(CONTROLLER_BUTTON_RIGHTSHOULDER);
    DEC_CONST(CONTROLLER_BUTTON_DPAD_UP);
    DEC_CONST(CONTROLLER_BUTTON_DPAD_DOWN);
    DEC_CONST(CONTROLLER_BUTTON_DPAD_LEFT);
    DEC_CONST(CONTROLLER_BUTTON_DPAD_RIGHT);
    DEC_CONST(CONTROLLER_BUTTON_MAX);

#else
    DEC_CONSTS(AUDIODEVICEADDED, -1);
    DEC_CONSTS(AUDIODEVICEREMOVED, -1);
    DEC_CONSTS(FINGERMOTION, -1);
    DEC_CONSTS(FINGERDOWN, -1);
    DEC_CONSTS(FINGERUP, -1);
    DEC_CONSTS(MULTIGESTURE, -1);
    DEC_CONSTS(MOUSEWHEEL, -1);
    DEC_CONSTS(TEXTINPUT, -1);
    DEC_CONSTS(TEXTEDITING, -1);
    DEC_CONSTS(WINDOWEVENT, -1);
    DEC_CONSTS(WINDOWEVENT_CLOSE, -1);

    DEC_CONSTS(CONTROLLERAXISMOTION, -1);
    DEC_CONSTS(CONTROLLERBUTTONDOWN, -1);
    DEC_CONSTS(CONTROLLERBUTTONUP, -1);
    DEC_CONSTS(CONTROLLERDEVICEADDED, -1);
    DEC_CONSTS(CONTROLLERDEVICEREMOVED, -1);
    DEC_CONSTS(CONTROLLERDEVICEREMAPPED, -1);

    DEC_CONST(BUTTON_WHEELUP);
    DEC_CONST(BUTTON_WHEELDOWN);
    DEC_CONSTS(AUDIO_ALLOW_FREQUENCY_CHANGE, -1);
    DEC_CONSTS(AUDIO_ALLOW_FORMAT_CHANGE, -1);
    DEC_CONSTS(AUDIO_ALLOW_CHANNELS_CHANGE, -1);
    DEC_CONSTS(AUDIO_ALLOW_ANY_CHANGE, -1);
    DEC_CONSTS(DROPFILE, -1);
    DEC_CONSTS(DROPTEXT, -1);
    DEC_CONSTS(DROPBEGIN, -1);
    DEC_CONSTS(DROPCOMPLETE, -1);
    DEC_CONSTS(CONTROLLER_AXIS_INVALID, -1);
    DEC_CONSTS(CONTROLLER_AXIS_LEFTX, -1);
    DEC_CONSTS(CONTROLLER_AXIS_LEFTY, -1);
    DEC_CONSTS(CONTROLLER_AXIS_RIGHTX, -1);
    DEC_CONSTS(CONTROLLER_AXIS_RIGHTY, -1);
    DEC_CONSTS(CONTROLLER_AXIS_TRIGGERLEFT, -1);
    DEC_CONSTS(CONTROLLER_AXIS_TRIGGERRIGHT, -1);
    DEC_CONSTS(CONTROLLER_AXIS_MAX, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_INVALID, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_A, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_B, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_X, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_Y, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_BACK, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_GUIDE, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_START, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_LEFTSTICK, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_RIGHTSTICK, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_LEFTSHOULDER, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_RIGHTSHOULDER, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_DPAD_UP, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_DPAD_DOWN, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_DPAD_LEFT, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_DPAD_RIGHT, -1);
    DEC_CONSTS(CONTROLLER_BUTTON_MAX, -1);
#if SDL_VERSION_ATLEAST(1, 2, 13)
    DEC_CONST(BUTTON_X1);
    DEC_CONST(BUTTON_X2);
#else
    PyModule_AddIntConstant(module, "BUTTON_X1", -1);
    PyModule_AddIntConstant(module, "BUTTON_X2", -1);
#endif
#endif

#if IS_SDLv1
    DEC_CONSTK(K_UNKNOWN);
    DEC_CONSTK(K_FIRST);
    DEC_CONSTK(K_BACKSPACE);
    DEC_CONSTK(K_TAB);
    DEC_CONSTK(K_CLEAR);
    DEC_CONSTK(K_RETURN);
    DEC_CONSTK(K_PAUSE);
    DEC_CONSTK(K_ESCAPE);
    DEC_CONSTK(K_SPACE);
    DEC_CONSTK(K_EXCLAIM);
    DEC_CONSTK(K_QUOTEDBL);
    DEC_CONSTK(K_HASH);
    DEC_CONSTK(K_DOLLAR);
    DEC_CONSTK(K_AMPERSAND);
    DEC_CONSTK(K_QUOTE);
    DEC_CONSTK(K_LEFTPAREN);
    DEC_CONSTK(K_RIGHTPAREN);
    DEC_CONSTK(K_ASTERISK);
    DEC_CONSTK(K_PLUS);
    DEC_CONSTK(K_COMMA);
    DEC_CONSTK(K_MINUS);
    DEC_CONSTK(K_PERIOD);
    DEC_CONSTK(K_SLASH);
    DEC_CONSTK(K_0);
    DEC_CONSTK(K_1);
    DEC_CONSTK(K_2);
    DEC_CONSTK(K_3);
    DEC_CONSTK(K_4);
    DEC_CONSTK(K_5);
    DEC_CONSTK(K_6);
    DEC_CONSTK(K_7);
    DEC_CONSTK(K_8);
    DEC_CONSTK(K_9);
    DEC_CONSTK(K_COLON);
    DEC_CONSTK(K_SEMICOLON);
    DEC_CONSTK(K_LESS);
    DEC_CONSTK(K_EQUALS);
    DEC_CONSTK(K_GREATER);
    DEC_CONSTK(K_QUESTION);
    DEC_CONSTK(K_AT);
    DEC_CONSTK(K_LEFTBRACKET);
    DEC_CONSTK(K_BACKSLASH);
    DEC_CONSTK(K_RIGHTBRACKET);
    DEC_CONSTK(K_CARET);
    DEC_CONSTK(K_UNDERSCORE);
    DEC_CONSTK(K_BACKQUOTE);
    DEC_CONSTK(K_a);
    DEC_CONSTK(K_b);
    DEC_CONSTK(K_c);
    DEC_CONSTK(K_d);
    DEC_CONSTK(K_e);
    DEC_CONSTK(K_f);
    DEC_CONSTK(K_g);
    DEC_CONSTK(K_h);
    DEC_CONSTK(K_i);
    DEC_CONSTK(K_j);
    DEC_CONSTK(K_k);
    DEC_CONSTK(K_l);
    DEC_CONSTK(K_m);
    DEC_CONSTK(K_n);
    DEC_CONSTK(K_o);
    DEC_CONSTK(K_p);
    DEC_CONSTK(K_q);
    DEC_CONSTK(K_r);
    DEC_CONSTK(K_s);
    DEC_CONSTK(K_t);
    DEC_CONSTK(K_u);
    DEC_CONSTK(K_v);
    DEC_CONSTK(K_w);
    DEC_CONSTK(K_x);
    DEC_CONSTK(K_y);
    DEC_CONSTK(K_z);
    DEC_CONSTK(K_DELETE);

    DEC_CONSTK(K_KP0);
    DEC_CONSTK(K_KP1);
    DEC_CONSTK(K_KP2);
    DEC_CONSTK(K_KP3);
    DEC_CONSTK(K_KP4);
    DEC_CONSTK(K_KP5);
    DEC_CONSTK(K_KP6);
    DEC_CONSTK(K_KP7);
    DEC_CONSTK(K_KP8);
    DEC_CONSTK(K_KP9);
    DEC_CONSTK(K_KP_PERIOD);
    DEC_CONSTK(K_KP_DIVIDE);
    DEC_CONSTK(K_KP_MULTIPLY);
    DEC_CONSTK(K_KP_MINUS);
    DEC_CONSTK(K_KP_PLUS);
    DEC_CONSTK(K_KP_ENTER);
    DEC_CONSTK(K_KP_EQUALS);
    DEC_CONSTK(K_UP);
    DEC_CONSTK(K_DOWN);
    DEC_CONSTK(K_RIGHT);
    DEC_CONSTK(K_LEFT);
    DEC_CONSTK(K_INSERT);
    DEC_CONSTK(K_HOME);
    DEC_CONSTK(K_END);
    DEC_CONSTK(K_PAGEUP);
    DEC_CONSTK(K_PAGEDOWN);
    DEC_CONSTK(K_F1);
    DEC_CONSTK(K_F2);
    DEC_CONSTK(K_F3);
    DEC_CONSTK(K_F4);
    DEC_CONSTK(K_F5);
    DEC_CONSTK(K_F6);
    DEC_CONSTK(K_F7);
    DEC_CONSTK(K_F8);
    DEC_CONSTK(K_F9);
    DEC_CONSTK(K_F10);
    DEC_CONSTK(K_F11);
    DEC_CONSTK(K_F12);
    DEC_CONSTK(K_F13);
    DEC_CONSTK(K_F14);
    DEC_CONSTK(K_F15);

    DEC_CONSTK(K_NUMLOCK);
    DEC_CONSTK(K_CAPSLOCK);
    DEC_CONSTK(K_SCROLLOCK);
    DEC_CONSTK(K_RSHIFT);
    DEC_CONSTK(K_LSHIFT);
    DEC_CONSTK(K_RCTRL);
    DEC_CONSTK(K_LCTRL);
    DEC_CONSTK(K_RALT);
    DEC_CONSTK(K_LALT);
    DEC_CONSTK(K_RMETA);
    DEC_CONSTK(K_LMETA);
    DEC_CONSTK(K_LSUPER);
    DEC_CONSTK(K_RSUPER);
    DEC_CONSTK(K_MODE);

    DEC_CONSTK(K_HELP);
    DEC_CONSTK(K_PRINT);
    DEC_CONSTK(K_SYSREQ);
    DEC_CONSTK(K_BREAK);
    DEC_CONSTK(K_MENU);
    DEC_CONSTK(K_POWER);
    DEC_CONSTK(K_EURO);
    DEC_CONSTK(K_LAST);
#else  /* IS_SDLv2 */
    /* Keyboard key codes: Pygame K_ constants. Scan codes: KSCAN_ constants.
     */
    DEC_CONSTK_AND_SC(UNKNOWN);
    DEC_CONSTK_AND_SC(BACKSPACE);
    DEC_CONSTK_AND_SC(TAB);
    DEC_CONSTK_AND_SC(CLEAR);
    DEC_CONSTK_AND_SC(RETURN);
    DEC_CONSTK_AND_SC(PAUSE);
    DEC_CONSTK_AND_SC(ESCAPE);
    DEC_CONSTK_AND_SC(SPACE);
    DEC_CONSTK(QUOTE); DEC_CONSTSC(APOSTROPHE);
    DEC_CONSTK_AND_SC(COMMA);
    DEC_CONSTK_AND_SC(MINUS);
    DEC_CONSTK_AND_SC(PERIOD);
    DEC_CONSTK_AND_SC(SLASH);
    DEC_CONSTK_AND_SC(0);
    DEC_CONSTK_AND_SC(1);
    DEC_CONSTK_AND_SC(2);
    DEC_CONSTK_AND_SC(3);
    DEC_CONSTK_AND_SC(4);
    DEC_CONSTK_AND_SC(5);
    DEC_CONSTK_AND_SC(6);
    DEC_CONSTK_AND_SC(7);
    DEC_CONSTK_AND_SC(8);
    DEC_CONSTK_AND_SC(9);
    DEC_CONSTK_AND_SC(SEMICOLON);
    DEC_CONSTK_AND_SC(EQUALS);
    DEC_CONSTK_AND_SC(LEFTBRACKET);
    DEC_CONSTK_AND_SC(BACKSLASH);
    DEC_CONSTK_AND_SC(RIGHTBRACKET);
    DEC_CONSTK(BACKQUOTE); DEC_CONSTSC(GRAVE);
    DEC_CONSTK(a); DEC_CONSTSC(A);
    DEC_CONSTK(b); DEC_CONSTSC(B);
    DEC_CONSTK(c); DEC_CONSTSC(C);
    DEC_CONSTK(d); DEC_CONSTSC(D);
    DEC_CONSTK(e); DEC_CONSTSC(E);
    DEC_CONSTK(f); DEC_CONSTSC(F);
    DEC_CONSTK(g); DEC_CONSTSC(G);
    DEC_CONSTK(h); DEC_CONSTSC(H);
    DEC_CONSTK(i); DEC_CONSTSC(I);
    DEC_CONSTK(j); DEC_CONSTSC(J);
    DEC_CONSTK(k); DEC_CONSTSC(K);
    DEC_CONSTK(l); DEC_CONSTSC(L);
    DEC_CONSTK(m); DEC_CONSTSC(M);
    DEC_CONSTK(n); DEC_CONSTSC(N);
    DEC_CONSTK(o); DEC_CONSTSC(O);
    DEC_CONSTK(p); DEC_CONSTSC(P);
    DEC_CONSTK(q); DEC_CONSTSC(Q);
    DEC_CONSTK(r); DEC_CONSTSC(R);
    DEC_CONSTK(s); DEC_CONSTSC(S);
    DEC_CONSTK(t); DEC_CONSTSC(T);
    DEC_CONSTK(u); DEC_CONSTSC(U);
    DEC_CONSTK(v); DEC_CONSTSC(V);
    DEC_CONSTK(w); DEC_CONSTSC(W);
    DEC_CONSTK(x); DEC_CONSTSC(X);
    DEC_CONSTK(y); DEC_CONSTSC(Y);
    DEC_CONSTK(z); DEC_CONSTSC(Z);
    DEC_CONSTK_AND_SC(DELETE);

    DEC_CONSTK_AND_SC(KP_0);
    DEC_CONSTK_AND_SC(KP_0);
    DEC_CONSTK_AND_SC(KP_1);
    DEC_CONSTK_AND_SC(KP_2);
    DEC_CONSTK_AND_SC(KP_3);
    DEC_CONSTK_AND_SC(KP_4);
    DEC_CONSTK_AND_SC(KP_5);
    DEC_CONSTK_AND_SC(KP_6);
    DEC_CONSTK_AND_SC(KP_7);
    DEC_CONSTK_AND_SC(KP_8);
    DEC_CONSTK_AND_SC(KP_9);
    DEC_CONSTKS_AND_SCS(KP1, KP_1);
    DEC_CONSTKS_AND_SCS(KP2, KP_2);
    DEC_CONSTKS_AND_SCS(KP3, KP_3);
    DEC_CONSTKS_AND_SCS(KP4, KP_4);
    DEC_CONSTKS_AND_SCS(KP5, KP_5);
    DEC_CONSTKS_AND_SCS(KP6, KP_6);
    DEC_CONSTKS_AND_SCS(KP7, KP_7);
    DEC_CONSTKS_AND_SCS(KP8, KP_8);
    DEC_CONSTKS_AND_SCS(KP9, KP_9);
    DEC_CONSTK_AND_SC(KP_PERIOD);
    DEC_CONSTK_AND_SC(KP_DIVIDE);
    DEC_CONSTK_AND_SC(KP_MULTIPLY);
    DEC_CONSTK_AND_SC(KP_MINUS);
    DEC_CONSTK_AND_SC(KP_PLUS);
    DEC_CONSTK_AND_SC(KP_ENTER);
    DEC_CONSTK_AND_SC(KP_EQUALS);
    DEC_CONSTK_AND_SC(UP);
    DEC_CONSTK_AND_SC(DOWN);
    DEC_CONSTK_AND_SC(RIGHT);
    DEC_CONSTK_AND_SC(LEFT);
    DEC_CONSTK_AND_SC(INSERT);
    DEC_CONSTK_AND_SC(HOME);
    DEC_CONSTK_AND_SC(END);
    DEC_CONSTK_AND_SC(PAGEUP);
    DEC_CONSTK_AND_SC(PAGEDOWN);
    DEC_CONSTK_AND_SC(F1);
    DEC_CONSTK_AND_SC(F2);
    DEC_CONSTK_AND_SC(F3);
    DEC_CONSTK_AND_SC(F4);
    DEC_CONSTK_AND_SC(F5);
    DEC_CONSTK_AND_SC(F6);
    DEC_CONSTK_AND_SC(F7);
    DEC_CONSTK_AND_SC(F8);
    DEC_CONSTK_AND_SC(F9);
    DEC_CONSTK_AND_SC(F10);
    DEC_CONSTK_AND_SC(F11);
    DEC_CONSTK_AND_SC(F12);
    DEC_CONSTK_AND_SC(F13);
    DEC_CONSTK_AND_SC(F14);
    DEC_CONSTK_AND_SC(F15);

    DEC_CONSTK_AND_SC(NUMLOCKCLEAR)
    DEC_CONSTKS_AND_SCS(NUMLOCK, NUMLOCKCLEAR);
    DEC_CONSTK_AND_SC(CAPSLOCK);
    DEC_CONSTK_AND_SC(SCROLLLOCK);
    DEC_CONSTKS_AND_SCS(SCROLLOCK, SCROLLLOCK);
    DEC_CONSTK_AND_SC(RSHIFT);
    DEC_CONSTK_AND_SC(LSHIFT);
    DEC_CONSTK_AND_SC(RCTRL);
    DEC_CONSTK_AND_SC(LCTRL);
    DEC_CONSTK_AND_SC(RALT);
    DEC_CONSTK_AND_SC(LALT);
    DEC_CONSTK_AND_SC(RGUI);
    DEC_CONSTKS_AND_SCS(RMETA, RGUI);
    DEC_CONSTK_AND_SC(LGUI);
    DEC_CONSTKS_AND_SCS(LMETA, LGUI);
    DEC_CONSTKS_AND_SCS(LSUPER, LGUI);
    DEC_CONSTKS_AND_SCS(RSUPER, RGUI);
    DEC_CONSTK_AND_SC(MODE);

    DEC_CONSTK_AND_SC(HELP);
    DEC_CONSTK_AND_SC(PRINTSCREEN);
    DEC_CONSTKS_AND_SCS(PRINT, PRINTSCREEN);
    DEC_CONSTK_AND_SC(SYSREQ);
    DEC_CONSTKS_AND_SCS(BREAK, PAUSE);
    DEC_CONSTK_AND_SC(MENU);
    DEC_CONSTK_AND_SC(POWER);
    DEC_CONSTK_AND_SC(CURRENCYUNIT);
    DEC_CONSTK_AND_SC(CURRENCYSUBUNIT);
    DEC_CONSTKS_AND_SCS(EURO, CURRENCYUNIT);

    DEC_CONSTSC(INTERNATIONAL1);
    DEC_CONSTSC(INTERNATIONAL2);
    DEC_CONSTSC(INTERNATIONAL3);
    DEC_CONSTSC(INTERNATIONAL4);
    DEC_CONSTSC(INTERNATIONAL5);
    DEC_CONSTSC(INTERNATIONAL6);
    DEC_CONSTSC(INTERNATIONAL7);
    DEC_CONSTSC(INTERNATIONAL8);
    DEC_CONSTSC(INTERNATIONAL9);
    DEC_CONSTSC(LANG1);
    DEC_CONSTSC(LANG2);
    DEC_CONSTSC(LANG3);
    DEC_CONSTSC(LANG4);
    DEC_CONSTSC(LANG5);
    DEC_CONSTSC(LANG6);
    DEC_CONSTSC(LANG7);
    DEC_CONSTSC(LANG8);
    DEC_CONSTSC(LANG9);
    DEC_CONSTSC(NONUSBACKSLASH);
    DEC_CONSTSC(NONUSHASH);

    DEC_CONSTK_AND_SC(UNKNOWN);
    DEC_CONSTK_AND_SC(BACKSPACE);
    DEC_CONSTK_AND_SC(TAB);
    DEC_CONSTK_AND_SC(CLEAR);
    DEC_CONSTK_AND_SC(RETURN);
    DEC_CONSTK_AND_SC(PAUSE);
    DEC_CONSTK_AND_SC(ESCAPE);
    DEC_CONSTK_AND_SC(SPACE);
    DEC_CONSTK(EXCLAIM);
    DEC_CONSTK(QUOTEDBL);
    DEC_CONSTK(HASH);
    DEC_CONSTK(DOLLAR);
    DEC_CONSTK(AMPERSAND);
    DEC_CONSTK(PERCENT);
    DEC_CONSTK(LEFTPAREN);
    DEC_CONSTK(RIGHTPAREN);
    DEC_CONSTK(ASTERISK);
    DEC_CONSTK(PLUS);
    DEC_CONSTK_AND_SC(COMMA);
    DEC_CONSTK_AND_SC(MINUS);
    DEC_CONSTK_AND_SC(PERIOD);
    DEC_CONSTK_AND_SC(SLASH);
    DEC_CONSTK_AND_SC(0);
    DEC_CONSTK_AND_SC(1);
    DEC_CONSTK_AND_SC(2);
    DEC_CONSTK_AND_SC(3);
    DEC_CONSTK_AND_SC(4);
    DEC_CONSTK_AND_SC(5);
    DEC_CONSTK_AND_SC(6);
    DEC_CONSTK_AND_SC(7);
    DEC_CONSTK_AND_SC(8);
    DEC_CONSTK_AND_SC(9);
    DEC_CONSTK(COLON);
    DEC_CONSTK_AND_SC(SEMICOLON);
    DEC_CONSTK(LESS);
    DEC_CONSTK_AND_SC(EQUALS);
    DEC_CONSTK(GREATER);
    DEC_CONSTK(QUESTION);
    DEC_CONSTK(AT);
    DEC_CONSTK_AND_SC(LEFTBRACKET);
    DEC_CONSTK_AND_SC(BACKSLASH);
    DEC_CONSTK_AND_SC(RIGHTBRACKET);
    DEC_CONSTK(CARET);
    DEC_CONSTK(UNDERSCORE);
    DEC_CONSTK_AND_SC(DELETE);

    DEC_CONSTKS_AND_SCS(KP0, KP_0);
    DEC_CONSTKS_AND_SCS(KP1, KP_1);
    DEC_CONSTKS_AND_SCS(KP2, KP_2);
    DEC_CONSTKS_AND_SCS(KP3, KP_3);
    DEC_CONSTKS_AND_SCS(KP4, KP_4);
    DEC_CONSTKS_AND_SCS(KP5, KP_5);
    DEC_CONSTKS_AND_SCS(KP6, KP_6);
    DEC_CONSTKS_AND_SCS(KP7, KP_7);
    DEC_CONSTKS_AND_SCS(KP8, KP_8);
    DEC_CONSTKS_AND_SCS(KP9, KP_9);
    DEC_CONSTK_AND_SC(KP_PERIOD);
    DEC_CONSTK_AND_SC(KP_DIVIDE);
    DEC_CONSTK_AND_SC(KP_MULTIPLY);
    DEC_CONSTK_AND_SC(KP_MINUS);
    DEC_CONSTK_AND_SC(KP_PLUS);
    DEC_CONSTK_AND_SC(KP_ENTER);
    DEC_CONSTK_AND_SC(KP_EQUALS);
    DEC_CONSTK_AND_SC(UP);
    DEC_CONSTK_AND_SC(DOWN);
    DEC_CONSTK_AND_SC(RIGHT);
    DEC_CONSTK_AND_SC(LEFT);
    DEC_CONSTK_AND_SC(INSERT);
    DEC_CONSTK_AND_SC(HOME);
    DEC_CONSTK_AND_SC(END);
    DEC_CONSTK_AND_SC(PAGEUP);
    DEC_CONSTK_AND_SC(PAGEDOWN);
    DEC_CONSTK_AND_SC(F1);
    DEC_CONSTK_AND_SC(F2);
    DEC_CONSTK_AND_SC(F3);
    DEC_CONSTK_AND_SC(F4);
    DEC_CONSTK_AND_SC(F5);
    DEC_CONSTK_AND_SC(F6);
    DEC_CONSTK_AND_SC(F7);
    DEC_CONSTK_AND_SC(F8);
    DEC_CONSTK_AND_SC(F9);
    DEC_CONSTK_AND_SC(F10);
    DEC_CONSTK_AND_SC(F11);
    DEC_CONSTK_AND_SC(F12);
    DEC_CONSTK_AND_SC(F13);
    DEC_CONSTK_AND_SC(F14);
    DEC_CONSTK_AND_SC(F15);

    DEC_CONSTK_AND_SC(NUMLOCKCLEAR)
    DEC_CONSTKS_AND_SCS(NUMLOCK, NUMLOCKCLEAR);
    DEC_CONSTK_AND_SC(CAPSLOCK);
    DEC_CONSTK_AND_SC(SCROLLLOCK);
    DEC_CONSTKS_AND_SCS(SCROLLOCK, SCROLLLOCK);
    DEC_CONSTK_AND_SC(RSHIFT);
    DEC_CONSTK_AND_SC(LSHIFT);
    DEC_CONSTK_AND_SC(RCTRL);
    DEC_CONSTK_AND_SC(LCTRL);
    DEC_CONSTK_AND_SC(RALT);
    DEC_CONSTK_AND_SC(LALT);
    DEC_CONSTK_AND_SC(RGUI);
    DEC_CONSTKS_AND_SCS(RMETA, RGUI);
    DEC_CONSTK_AND_SC(LGUI);
    DEC_CONSTKS_AND_SCS(LMETA, LGUI);
    DEC_CONSTKS_AND_SCS(LSUPER, LGUI);
    DEC_CONSTKS_AND_SCS(RSUPER, RGUI);
    DEC_CONSTK_AND_SC(MODE);

    DEC_CONSTK_AND_SC(HELP);
    DEC_CONSTK_AND_SC(PRINTSCREEN);
    DEC_CONSTKS_AND_SCS(PRINT, PRINTSCREEN);
    DEC_CONSTK_AND_SC(SYSREQ);
    DEC_CONSTKS_AND_SCS(BREAK, PAUSE);
    DEC_CONSTK_AND_SC(MENU);
    DEC_CONSTK_AND_SC(POWER);
    DEC_CONSTK_AND_SC(CURRENCYUNIT);
    DEC_CONSTK_AND_SC(CURRENCYSUBUNIT);
    DEC_CONSTKS_AND_SCS(EURO, CURRENCYUNIT);
#endif /* IS_SDLv2 */

    /* Keyboard key modifiers: Pygame KMOD_ constants.
     */
    DEC_CONSTN(KMOD_NONE);
    DEC_CONSTN(KMOD_LSHIFT);
    DEC_CONSTN(KMOD_RSHIFT);
    DEC_CONSTN(KMOD_LCTRL);
    DEC_CONSTN(KMOD_RCTRL);
    DEC_CONSTN(KMOD_LALT);
    DEC_CONSTN(KMOD_RALT);
#if IS_SDLv1
    DEC_CONSTN(KMOD_LMETA);
    DEC_CONSTN(KMOD_RMETA);
#else  /* IS_SDLv2 */
    DEC_CONSTN(KMOD_LGUI);
    DEC_CONSTS(KMOD_LMETA, KMOD_LGUI);
    DEC_CONSTN(KMOD_RGUI);
    DEC_CONSTS(KMOD_RMETA, KMOD_RGUI);
#endif /* IS_SDLv2 */
    DEC_CONSTN(KMOD_NUM);
    DEC_CONSTN(KMOD_CAPS);
    DEC_CONSTN(KMOD_MODE);

    DEC_CONSTN(KMOD_CTRL);
    DEC_CONSTN(KMOD_SHIFT);
    DEC_CONSTN(KMOD_ALT);
#if IS_SDLv1
    DEC_CONSTN(KMOD_META);
#else  /* IS_SDLv2 */
    DEC_CONSTN(KMOD_GUI);
    DEC_CONSTS(KMOD_META, KMOD_GUI);

    DEC_CONST(APPFOCUSMOUSE);
    DEC_CONST(APPINPUTFOCUS);
    DEC_CONST(APPACTIVE);
#endif /* IS_SDLv2 */

#define PYGAME_USEREVENT_DROPFILE 0x1000
    DEC_CONSTS(USEREVENT_DROPFILE, PYGAME_USEREVENT_DROPFILE);

    MODINIT_RETURN(module);
}

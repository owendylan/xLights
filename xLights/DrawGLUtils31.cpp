
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef __WXMAC__
#include "OpenGL/gl3.h"
#define __gl_h_
#else

#include "wx/wx.h"

#include <GL/gl.h>
    #ifdef _MSC_VER
        #include "GL/glext.h"
        //#include "GL/glut.h"
    #else
        #include <GL/glext.h>
    #endif
#endif

#include "DrawGLUtils.h"
#include <stack>

#include <log4cpp/Category.hh>

#ifndef __WXMAC__

PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLUNIFORM4FPROC glUniform4f;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange;
PFNGLMAPBUFFERRANGEPROC glMapBufferRange;
PFNGLUNMAPBUFFERPROC glUnmapBuffer;
#ifndef LINUX
PFNGLACTIVETEXTUREPROC glActiveTexture;
#endif
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;

#ifdef LINUX // conversion function from glx to wgl calls
__GLXextFuncPtr wglGetProcAddress(const char* a) {
    return glXGetProcAddress((const GLubyte*)a);
}
#endif


void LoadGLFunctions() {
    glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
    glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
    glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
    glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
    glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
    glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
    glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
    glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
    glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
    glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
    glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
    glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
    glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
    glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
    glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
    glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
    glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)wglGetProcAddress("glFlushMappedBufferRange");
    glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)wglGetProcAddress("glMapBufferRange");
    glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)wglGetProcAddress("glUnmapBuffer");
#ifndef LINUX
    glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
#endif
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
    glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
    glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
}
#else
void LoadGLFunctions() {
}
#endif

class ShaderProgram {
public:
    ShaderProgram() : buffers(nullptr), numBuffers(0) {}
    
    void Cleanup() {
        LOG_GL_ERRORV(glUseProgram(0));
        LOG_GL_ERRORV(glDeleteBuffers(numBuffers, buffers));
        LOG_GL_ERRORV(glDeleteProgram(ProgramID));
        delete [] buffers;
        LOG_GL_ERRORV(glDeleteVertexArrays(1, &VertexArrayID));
    }
    GLuint GetBufferID(int idx) {
        return buffers[idx];
    }
    void UseProgram() {
        LOG_GL_ERRORV(glUseProgram(ProgramID));
    }
    void SetMatrix(glm::mat4 &m) {
        LOG_GL_ERRORV(glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(m)));
    }
    void SetRenderType(int i) {
        LOG_GL_ERRORV(glUniform1i(RenderTypeID, i));
    }
    void BindBuffer(int idx, void *data, int sz) {
        LOG_GL_ERRORV(glEnableVertexAttribArray(idx));
        LOG_GL_ERRORV(glBindBuffer(GL_ARRAY_BUFFER, buffers[idx]));
        LOG_GL_ERRORV(glBufferData(GL_ARRAY_BUFFER, sz, data, GL_DYNAMIC_DRAW));
    }
    void UnbindBuffer(int idx) {
        LOG_GL_ERRORV(glDisableVertexAttribArray(idx));
        LOG_GL_ERRORV(glBindBuffer(GL_ARRAY_BUFFER, buffers[idx]));
        LOG_GL_ERRORV(glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW));
        LOG_GL_ERRORV(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
    
    void Init(const char * vs, const char * fs, int numBuf) {
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        CompileShader(vs, VertexShaderID);
        CompileShader(fs, FragmentShaderID);
        ProgramID = CreateProgram(VertexShaderID, FragmentShaderID);
        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);
        
        UseProgram();
        LOG_GL_ERRORV(MatrixID = glGetUniformLocation(ProgramID, "MVP"));
        LOG_GL_ERRORV(PointSmoothMinID = glGetUniformLocation(ProgramID, "PointSmoothMin"));
        LOG_GL_ERRORV(PointSmoothMaxID = glGetUniformLocation(ProgramID, "PointSmoothMax"));
        LOG_GL_ERRORV(RenderTypeID = glGetUniformLocation(ProgramID, "RenderType"));

        
        numBuffers = numBuf;
        buffers = new GLuint[numBuffers];
        LOG_GL_ERRORV(glGenVertexArrays(1, &VertexArrayID));
        LOG_GL_ERRORV(glGenBuffers(numBuffers, buffers));
        LOG_GL_ERRORV(glBindVertexArray(VertexArrayID));
    }
    
    float CalcSmoothPointParams() {
        float ps;
        LOG_GL_ERRORV(glGetFloatv(GL_POINT_SIZE, &ps));
        LOG_GL_ERRORV(glPointSize(ps+1));
        float delta = 1.0 / (ps+1);
        float mid = 0.35 + 0.15 * ((ps - 1.0f)/25.0f);
        if (mid > 0.5) {
            mid = 0.5;
        }
        
        float min = std::max(0.0f, mid - delta);
        float max = std::min(1.0f, mid + delta);
        LOG_GL_ERRORV(glUniform1f(PointSmoothMinID, min));
        LOG_GL_ERRORV(glUniform1f(PointSmoothMaxID, max));
        return ps;
    }

    static GLuint CreateProgram(GLuint vs, GLuint fs) {
        GLuint ProgramID = glCreateProgram();
        LOG_GL_ERRORV(glAttachShader(ProgramID, vs));
        LOG_GL_ERRORV(glAttachShader(ProgramID, fs));
        LOG_GL_ERRORV(glLinkProgram(ProgramID));
        
        
        GLint Result = GL_FALSE;
        int InfoLogLength;
        
        LOG_GL_ERRORV(glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result));
        LOG_GL_ERRORV(glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength));
        if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            wxString l = &ProgramErrorMessage[0];
            l.Trim();
            if (l.length() > 0) {
                printf("Program Log: %s\n", &ProgramErrorMessage[0]);
                log4cpp::Category &logger_opengl = log4cpp::Category::getInstance(std::string("log_opengl"));
                logger_opengl.error(std::string(&ProgramErrorMessage[0]));
            }
        }
        LOG_GL_ERRORV(glDetachShader(ProgramID, vs));
        LOG_GL_ERRORV(glDetachShader(ProgramID, fs));
        return ProgramID;
    }
    
    static void CompileShader(const char *sourcePointer, GLuint shaderID) {
        LOG_GL_ERRORV(glShaderSource(shaderID, 1, &sourcePointer , NULL));
        LOG_GL_ERRORV(glCompileShader(shaderID));
        
        GLint Result = GL_FALSE;
        int InfoLogLength;
        
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ) {
            std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            wxString l = &VertexShaderErrorMessage[0];
            l.Trim();
            if (l.length() > 0) {
                printf("Shader Log: %s\n", &VertexShaderErrorMessage[0]);
                log4cpp::Category &logger_opengl = log4cpp::Category::getInstance(std::string("log_opengl"));
                logger_opengl.error(std::string(&VertexShaderErrorMessage[0]));
            }
        }
    }

    
    GLuint ProgramID;
    GLuint VertexArrayID;
    
    GLuint *buffers;
    size_t numBuffers;
    
    GLuint MatrixID;
    GLuint PointSmoothMinID;
    GLuint PointSmoothMaxID;
    GLuint RenderTypeID;
};



class OpenGL33Cache : public DrawGLUtils::xlGLCacheInfo {
    
    int UsageCount = 0;
    
    ShaderProgram textureProgram;
    ShaderProgram singleColorProgram;
    ShaderProgram normalProgram;
    ShaderProgram vbNormalProgram;
    
    void Load33Shaders() {
        if (UsageCount == 0) {
            textureProgram.Init(
                                "#version 330 core\n"
                                "layout(location = 0) in vec2 vertexPosition_modelspace;\n"
                                "layout(location = 1) in vec2 vertexUV;\n"
                                "out vec4 fragmentColor;\n"
                                "out vec2 UV;\n"
                                "uniform mat4 MVP;\n"
                                "uniform vec4 inColor;\n"
                                "void main(){\n"
                                "    gl_Position = MVP * vec4(vertexPosition_modelspace,0,1);\n"
                                "    fragmentColor = inColor;\n"
                                "    UV = vertexUV;\n"
                                "}\n",
                                
                                "#version 330 core\n"
                                "in vec4 fragmentColor;\n"
                                "in vec2 UV;\n"
                                "out vec4 color;\n"
                                "uniform sampler2D tex;\n"
                                "uniform int RenderType;\n"
                                "void main(){\n"
                                "    vec4 c = texture(tex, UV);\n"
                                "    color = vec4(c.rgb, c.a*fragmentColor.a);\n"
                                "}\n", 2);
            
            
            singleColorProgram.Init(
                                    "#version 330 core\n"
                                    "layout(location = 0) in vec2 vertexPosition_modelspace;\n"
                                    "out vec4 fragmentColor;\n"
                                    "uniform mat4 MVP;\n"
                                    "uniform vec4 inColor;\n"
                                    "void main(){\n"
                                    "    gl_Position = MVP * vec4(vertexPosition_modelspace,0,1);"
                                    "    fragmentColor = inColor;\n"
                                    "}\n",
                                    "#version 330 core\n"
                                    "in vec4 fragmentColor;\n"
                                    "out vec4 color;\n"
                                    "uniform int RenderType = 0;\n"
                                    "uniform float PointSmoothMin = 0.4;\n"
                                    "uniform float PointSmoothMax = 0.5;\n"
                                    "void main(){\n"
                                    "    if (RenderType == 0) {\n"
                                    "        color = fragmentColor;\n"
                                    "    } else {\n"
                                    "        float dist = distance(gl_PointCoord, vec2(0.5));\n"
                                    "        float alpha = 1.0 - smoothstep(PointSmoothMin, PointSmoothMax, dist);\n"
                                    "        if (alpha == 0.0) discard;\n"
                                    "        alpha = alpha * fragmentColor.a;\n"
                                    "        color = vec4(fragmentColor.rgb, alpha);\n"
                                    "    }\n"
                                    "}\n", 1);
            
            const char *npVS = "#version 330 core\n"
                                "layout(location = 0) in vec2 vertexPosition_modelspace;\n"
                                "layout(location = 1) in vec4 vertexColor;\n"
                                "out vec4 fragmentColor;\n"
                                "uniform int RenderType;\n"
                                "uniform mat4 MVP;\n"
                                "uniform vec4 inColor;\n"
                                "void main(){\n"
                                "    gl_Position = MVP * vec4(vertexPosition_modelspace,0,1);\n"
                                "    if (RenderType == -2) {\n"
                                "        fragmentColor = inColor;\n"
                                "    } else if (RenderType == -1) {\n"
                                "        fragmentColor = inColor;\n"
                                "    } else {\n"
                                "        fragmentColor = vertexColor;\n"
                                "    }\n"
                                "}\n";
            const char *npFS = "#version 330 core\n"
                                "in vec4 fragmentColor;\n"
                                "in vec2 UV;\n"
                                "out vec4 color;\n"
                                "uniform int RenderType;\n"
                                "uniform float PointSmoothMin = 0.4;\n"
                                "uniform float PointSmoothMax = 0.5;\n"
                                "void main(){\n"
                                "    if (RenderType == 0 || RenderType == -2) {\n"
                                "        color = fragmentColor;\n"
                                "    } else {\n"
                                "        float dist = distance(gl_PointCoord, vec2(0.5));\n"
                                "        float alpha = 1.0 - smoothstep(PointSmoothMin, PointSmoothMax, dist);\n"
                                "        if (alpha == 0.0) discard;\n"
                                "        alpha = alpha * fragmentColor.a;\n"
                                "        color = vec4(fragmentColor.rgb, alpha);\n"
                                "    }\n"
                                "}\n";
            
            normalProgram.Init(npVS, npFS, 2);
            vbNormalProgram.Init(npVS, npFS, 2);
        }
        UsageCount++;
    }
    void Release33Shaders() {
        UsageCount--;
        if (UsageCount == 0) {
            singleColorProgram.Cleanup();
            textureProgram.Cleanup();
            normalProgram.Cleanup();
        }
    }
    

public:
    OpenGL33Cache() : matrix(nullptr), colors(4), vertices(2) {
        Load33Shaders();
        InitializeVertexBuffer();
    }
    ~OpenGL33Cache() {
        if (matrix) {
            delete matrix;
        }
        while (!matrixStack.empty()) {
            delete matrixStack.top();
            matrixStack.pop();
        }
        CleanupVertexBuffer();
        Release33Shaders();
    }

    virtual bool IsCoreProfile() override { return true;}

    void Draw(DrawGLUtils::xlVertexAccumulator &va, const xlColor & color, int type, int enableCapability) override {
        if (va.count == 0) {
            return;
        }
        glGetError();
        singleColorProgram.UseProgram();
        singleColorProgram.SetMatrix(*matrix);
        singleColorProgram.BindBuffer(0, &va.vertices[0], va.count*2*sizeof(GLfloat));
        LOG_GL_ERRORV(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

        GLuint cid = glGetUniformLocation(singleColorProgram.ProgramID, "inColor");
        glUniform4f(cid,
                    ((float)color.Red())/255.0,
                    ((float)color.Green())/255.0,
                    ((float)color.Blue())/255.0,
                    ((float)color.Alpha())/255.0
                    );
        float ps = 0;
        if (type == GL_POINTS && enableCapability == 0x0B10) {
            //POINT_SMOOTH, removed in OpenGL3.x
            singleColorProgram.SetRenderType(1);
            ps = singleColorProgram.CalcSmoothPointParams();
        } else if (enableCapability > 0) {
            glEnable(enableCapability);
        }
        glDrawArrays(type, 0, va.count);
        if (type == GL_POINTS && enableCapability == 0x0B10) {
            singleColorProgram.SetRenderType(0);
        } else if (enableCapability > 0) {
            glDisable(enableCapability);
        }
        singleColorProgram.UnbindBuffer(0);
    }

    void Draw(DrawGLUtils::xlVertexColorAccumulator &va, int type, int enableCapability) override {
        if (va.count == 0) {
            return;
        }
//        glGetError();
        normalProgram.UseProgram();
        normalProgram.SetMatrix(*matrix);

        normalProgram.BindBuffer(0, &va.vertices[0], va.count*2*sizeof(GLfloat));
        LOG_GL_ERRORV(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

        normalProgram.BindBuffer(1, &va.colors[0], va.count*4*sizeof(GLubyte));
        LOG_GL_ERRORV(glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0 ));

        float ps = 2.0;
        if (type == GL_POINTS && enableCapability == 0x0B10) {
            //POINT_SMOOTH, removed in OpenGL3.x
            normalProgram.SetRenderType(1);
            ps = normalProgram.CalcSmoothPointParams();
        } else {
            if (enableCapability > 0) {
                glEnable(enableCapability);
            } else if (enableCapability != 0) {
                normalProgram.SetRenderType(enableCapability);
            }
        }
        LOG_GL_ERRORV(glDrawArrays(type, 0, va.count));
        if (type == GL_POINTS && enableCapability == 0x0B10) {
            normalProgram.SetRenderType(0);
            glPointSize(ps);
        } else if (enableCapability > 0) {
            glDisable(enableCapability);
        } else if (enableCapability != 0) {
            normalProgram.SetRenderType(0);
        }
        
        normalProgram.UnbindBuffer(0);
        normalProgram.UnbindBuffer(1);
    }
    void Draw(DrawGLUtils::xlVertexTextureAccumulator &va, int type, int enableCapability) override {
        if (va.count == 0) {
            return;
        }
        glGetError();
        textureProgram.UseProgram();
        textureProgram.SetMatrix(*matrix);

        textureProgram.BindBuffer(0, &va.vertices[0], va.count*2*sizeof(GLfloat));
        LOG_GL_ERRORV(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

        textureProgram.BindBuffer(1, &va.tvertices[0], va.count*2*sizeof(GLfloat));
        LOG_GL_ERRORV(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

        LOG_GL_ERRORV(glActiveTexture(GL_TEXTURE0)); //switch to texture image unit 0
        LOG_GL_ERRORV(glBindTexture(GL_TEXTURE_2D, va.id));
        LOG_GL_ERRORV(glUniform1i(glGetUniformLocation(textureProgram.ProgramID, "tex"), 0));

        GLuint cid = glGetUniformLocation(textureProgram.ProgramID, "inColor");
        LOG_GL_ERRORV(glUniform4f(cid, 1.0, 1.0, 1.0, ((float)va.alpha)/255.0));

        if (enableCapability > 0) {
            glEnable(enableCapability);
        }
        LOG_GL_ERRORV(glDrawArrays(type, 0, va.count));
        if (enableCapability > 0) {
            glDisable(enableCapability);
        }
        textureProgram.UnbindBuffer(0);
        textureProgram.UnbindBuffer(1);
    }
#ifdef NO_OPTMIZED_PATH
    // Un-optimized that just feeds through the Draw(xlVertexColorAccumulator)
    void InitializeVertexBuffer() {}
    void CleanupVertexBuffer() {}

    DrawGLUtils::xlVertexColorAccumulator data;
    virtual void addVertex(float x, float y, const xlColor &c) override {
        data.PreAlloc(1);
        data.AddVertex(x, y, c);
    }
    virtual void ensureSize(unsigned int s) override {
        data.PreAlloc(s);
    }
    virtual unsigned int vertexCount() override {
        return data.count;
    }
    
    void flush(int type, int enableCapability) override {
        Draw(data, type, enableCapability);
        data.Reset();
    }
#else
    template <class T>
    class xlGLArray {
    public:
        xlGLArray(int sz) : mapped(false), array(nullptr), id(-1), size(sz), sizePerUnit(sz * sizeof(T)) {};
        ~xlGLArray() {
            if (!mapped && array) {
                delete [] array;
            }
        }
        void Init(int max, GLuint bufId) {
            id = bufId;
            ReInit(max);
        }
        void CleanUp() {
            if (id != -1) {
                LOG_GL_ERRORV(glBindBuffer(GL_ARRAY_BUFFER, id));
                if (mapped) {
                    LOG_GL_ERRORV(glUnmapBuffer(GL_ARRAY_BUFFER));
                    mapped = false;
                    array = nullptr;
                }
            }
        }
        
        void FlushAndUnmap(int start, int count) {
            LOG_GL_ERRORV(glBindBuffer(GL_ARRAY_BUFFER, id));
            if (mapped) {
                LOG_GL_ERRORV(glFlushMappedBufferRange(GL_ARRAY_BUFFER, 0 , count*sizePerUnit));
                LOG_GL_ERRORV(glUnmapBuffer(GL_ARRAY_BUFFER));
                mapped = false;
                array = nullptr;
            } else {
                LOG_GL_ERRORV(glBufferData(id, count*sizePerUnit, array, GL_DYNAMIC_DRAW));
                delete [] array;
                mapped = false;
                array = nullptr;
            }
        }
        
        void Remap(int start, int max) {
            LOG_GL_ERRORV(glBindBuffer(GL_ARRAY_BUFFER, id));
            LOG_GL_ERRORV(array = (T*)glMapBufferRange(GL_ARRAY_BUFFER, sizePerUnit*start, sizePerUnit*max,
                                                       GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_FLUSH_EXPLICIT_BIT | GL_MAP_UNSYNCHRONIZED_BIT));
            if (array) {
                mapped = true;
            } else {
                mapped = false;
                array = new T[max * size];
            }
        }
        
        void ReInit(int max) {
            LOG_GL_ERRORV(glBindBuffer(GL_ARRAY_BUFFER, id));
            LOG_GL_ERRORV(glBufferData(GL_ARRAY_BUFFER, max*sizePerUnit, nullptr, GL_DYNAMIC_DRAW));
            LOG_GL_ERRORV(array = (T*)glMapBufferRange(GL_ARRAY_BUFFER, 0, max*sizePerUnit,
                                                       GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_FLUSH_EXPLICIT_BIT | GL_MAP_UNSYNCHRONIZED_BIT));
            if (array) {
                mapped = true;
            } else {
                mapped = false;
                array = new T[max * size];
            }
        }
        
        void Resize(int start, int curCount, int newmax) {
            if (mapped) {
                FlushAndUnmap(start, curCount);
                
                LOG_GL_ERRORV(T *m = (T*)glMapBufferRange(GL_ARRAY_BUFFER, sizePerUnit*start,  sizePerUnit*curCount, GL_MAP_READ_BIT));
                T *tmpv = nullptr;
                if (m) {
                    tmpv = new T[curCount * size];
                    memcpy(tmpv, m, curCount*sizePerUnit);
                    LOG_GL_ERRORV(glUnmapBuffer(GL_ARRAY_BUFFER));
                }
                ReInit(newmax);
                if (tmpv) {
                    memcpy(array, tmpv, curCount*sizePerUnit);
                    delete [] tmpv;
                }
            } else {
                if (array) {
                    T *ar = new T[size * newmax];
                    memcpy(ar, &array[start * size], curCount*sizePerUnit);
                    delete [] array;
                    array = ar;
                } else {
                    array = new T[size * newmax];
                }
            }
        }
        
        T &operator[](int idx) {
            return array[idx];
        }
        
        int sizePerUnit;
        int size;
        GLuint id;
        bool mapped;
        T *array;
    };
    
    int max;
    int superMax;
    int start;
    int curCount;
    xlGLArray<uint8_t> colors;
    xlGLArray<float> vertices;

    void InitializeVertexBuffer() {
        max = superMax = 1024;
        curCount = 0;
        vbNormalProgram.UseProgram();
        LOG_GL_ERRORV(glEnableVertexAttribArray(0));
        vertices.Init(max, vbNormalProgram.GetBufferID(0));
        
        // 2nd attribute buffer : colors
        LOG_GL_ERRORV(glEnableVertexAttribArray(1));
        colors.Init(max, vbNormalProgram.GetBufferID(1));
        glVertexAttribPointer(1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                              4,                                // size
                              GL_UNSIGNED_BYTE,                 // type
                              GL_TRUE,                          // normalized?
                              0,                                // stride
                              (void*)0                          // array buffer offset
                              );
        
        start = 0;
    }
    void CleanupVertexBuffer() {
        vertices.CleanUp();
        colors.CleanUp();
    }

    virtual void addVertex(float x, float y, const xlColor &c) override {
        ensureSize(1);
        vertices[curCount * 2] = x;
        vertices[curCount * 2 + 1] = y;

        colors[curCount*4] = c.Red();
        colors[curCount*4 + 1] = c.Green();
        colors[curCount*4 + 2] = c.Blue();
        colors[curCount*4 + 3] = c.Alpha();
        curCount++;
    }
    virtual void ensureSize(unsigned int s) override {
        int size = curCount + s;
        if (size > max) {
            superMax = std::max(superMax, size);
            max = superMax;
            vertices.Resize(start, curCount, max);
            colors.Resize(start, curCount, max);
            if (curCount) {
                //so I can put a breakpoint
                start = 0;
            }
            start = 0;
        }
    }
    virtual unsigned int vertexCount() override {
        return curCount;
    }

    void flush(int type, int enableCapability) override {
        vbNormalProgram.UseProgram();
        vbNormalProgram.SetMatrix(*matrix);

        vertices.FlushAndUnmap(start, curCount);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );
        LOG_GL_ERRORV(glEnableVertexAttribArray(0));

        colors.FlushAndUnmap(start, curCount);
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0 );
        LOG_GL_ERRORV(glEnableVertexAttribArray(1));
        
        float ps;
        if (type == GL_POINTS && enableCapability == 0x0B10) {
            //POINT_SMOOTH, removed in OpenGL3.x
            ps = vbNormalProgram.CalcSmoothPointParams();
            vbNormalProgram.SetRenderType(1);
        } else {
            if (enableCapability > 0) {
                glEnable(enableCapability);
            } else if (enableCapability != 0) {
                vbNormalProgram.SetRenderType(enableCapability);
            }
        }
        LOG_GL_ERRORV(glDrawArrays(type, start, curCount));
        if (type == GL_POINTS && enableCapability == 0x0B10) {
            glPointSize(ps);
            vbNormalProgram.SetRenderType(0);
        } else if (enableCapability > 0) {
            glDisable(enableCapability);
        } else if (enableCapability != 0) {
            vbNormalProgram.SetRenderType(0);
        }
        start += curCount;
        max -= curCount;
        if (max < 64) {
            max = superMax;
            start = 0;
            vertices.ReInit(max);
            colors.ReInit(max);
        } else {
            vertices.Remap(start, max);
            colors.Remap(start, max);
        }
        curCount = 0;
        LOG_GL_ERRORV(glDisableVertexAttribArray(0));
        LOG_GL_ERRORV(glDisableVertexAttribArray(1));
    }
#endif
    
    void DrawTexture(GLuint* texture,
                     float x, float y, float x2, float y2,
                     float tx, float ty, float tx2, float ty2) override {
        DrawGLUtils::xlVertexTextureAccumulator va(*texture);
        va.PreAlloc(12);
        va.AddVertex(x, y, tx, ty);
        va.AddVertex(x2, y, tx2, ty);
        va.AddVertex(x2, y2, tx2, ty2);
        va.AddVertex(x2, y2, tx2, ty2);
        va.AddVertex(x, y2, tx, ty2);
        va.AddVertex(x, y, tx, ty);
        Draw(va, GL_TRIANGLES, 0);
    }

    void Ortho(int topleft_x, int topleft_y, int bottomright_x, int bottomright_y) override {
        if (matrix) {
            delete matrix;
        }
        glm::mat4 m = glm::ortho((float)topleft_x, (float)bottomright_x, (float)bottomright_y, (float)topleft_y);
        matrix = new glm::mat4(m);
    }
    void PushMatrix() override {
        matrixStack.push(matrix);
        matrix = new glm::mat4(*matrix);
    }
    void PopMatrix() override {
        if (!matrixStack.empty()) {
            if (matrix != nullptr) {
                delete matrix;
            }
            matrix = matrixStack.top();
            matrixStack.pop();
        }
    }
    void Translate(float x, float y, float z) override {
        if (matrix) {
            glm::mat4 tm = glm::translate(*matrix, glm::vec3(x, y, z));
            delete matrix;
            matrix = new glm::mat4(tm);
        } else {
            glm::mat4 tm = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
            matrix = new glm::mat4(tm);
        }
    }
    void Rotate(float angle, float x, float y, float z) override {
        if (matrix) {
            angle = wxDegToRad(angle);
            glm::mat4 tm = glm::rotate(*matrix, angle, glm::vec3(x, y, z));
            delete matrix;
            matrix = new glm::mat4(tm);
        } else {
            angle = wxDegToRad(angle);
            glm::mat4 tm = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(x, y, z));
            matrix = new glm::mat4(tm);
        }
    }
    void Scale(float w, float h, float z) override {
        if (matrix) {
            glm::mat4 tm = glm::scale(*matrix, glm::vec3(w, h, z));
            delete matrix;
            matrix = new glm::mat4(tm);
        } else {
            glm::mat4 tm = glm::scale(glm::mat4(1.0f), glm::vec3(w, h, z));
            matrix = new glm::mat4(tm);
        }
    }


protected:


    std::stack<glm::mat4*> matrixStack;
    glm::mat4 *matrix;
};


DrawGLUtils::xlGLCacheInfo *Create33Cache() {
    return new OpenGL33Cache();
}

#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include <GL/glew.h>
#include "Shader.h"

class PostProcessor {
public:
    PostProcessor();
    ~PostProcessor();

    bool init(int width, int height);
    bool resize(int width, int height);
    void beginScene() const;
    void render(Shader& postShader) const;

    GLuint getFramebuffer() const { return framebuffer; }

private:
    GLuint framebuffer;
    GLuint colorTexture;
    GLuint objectIdTexture;
    GLuint depthTexture;
    GLuint quadVAO;
    GLuint quadVBO;
    int width;
    int height;

    bool createTargets(int newWidth, int newHeight);
    void destroyTargets();
};

#endif

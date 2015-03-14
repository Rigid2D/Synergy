/**
* @brief MarchingCubesRenderer
*
*/

#pragma once

#include <Synergy/Synergy.hpp>

//-- For vao_voxelData:
const GLuint uvCoord_attrib_index = 0;
const GLuint zLayerCoord_attrib_index = 1;

//-- For vao_isoSurfaceTriangles:
const GLuint position_attrib_index = 0;
const GLuint normal_attrib_index = 1;

//-- Streams for transform feedback buffers
const GLuint streamIndex_wsPositions = 0;
const GLuint streamIndex_wsNormals = 1;

//-- Texture Unit Offsets:
const GLint volumeData_texUnitOffset = 0;
const GLint triTable_texUnitOffset = 1;


/**
* Given a 3D density texture density of dimension (gridWidth, gridHeight, gridDepth), this
* class will run the Marching Cubes algorithm which will generate
* (gridWidth-1)*(gridHeight-1)*(gridDepth-1) voxels with density values at the corner of
* each voxel.  From there triangles will be generated from voxel edge crossing of the
* iso-surface.
*/
class MarchingCubesRenderer {
    

public:
    MarchingCubesRenderer(Synergy::uint32 gridWidth,
                          Synergy::uint32 gridHeight,
                          Synergy::uint32 gridDepth);

    ~MarchingCubesRenderer();

    void render(const Synergy::Camera & camera,
                GLuint volumeData_texture3d,
                Synergy::float32 isoSurfaceThreshold);

private:
    Synergy::float32 gridWidth;
    Synergy::float32 gridHeight;
    Synergy::float32 gridDepth;
    GLsizei numVoxelsPerLayer;
    GLsizei transformFeedbackBufferSize;
    GLuint sampler_volumeData;

    //-- Shaders:
    Synergy::ShaderProgram shaderProgram_genIsoSurface;
    Synergy::ShaderProgram shaderProgram_renderIsoSurface;
    Synergy::ShaderProgram shaderProgram_voxelEdges;

    //-- Vertex Array Objects:
    GLuint vao_voxelData; // For generating MC voxel data.
    GLuint vao_isoSurfaceTriangles; // For isosurface triangles rendering.
    GLuint vao_voxelEdgeLines; // For voxel edge line rendering.

    //-- Vertex Buffers:
    GLuint vbo_voxelUvCoords;  // texture coordinate for lower-left corner of each voxel.
    GLuint vbo_voxelZLayer;  // texture z layer of each voxel.
    GLuint streamBuffer_wsPositions; // For transform feedback.
    GLuint streamBuffer_wsNormals; // For transform feedback.
    GLuint voxelEdges_vertexBuffer; // Vertex data for voxel edge lines.
    GLuint voxelEdges_indexBuffer; // Indices for voxel edge lines.


    // Table for mapping mc_case to edges cut by isosurface.
    GLuint triTable_texture2d;

    // Used for gathering transform feedback primitive counts written.
    GLuint transformFeedbackObj;


    void setupVoxelUvCoordVboData();
    void setupVaoForVoxelData();
    void setupShaders();
    void setShaderUniforms();
    void uploadUniformArrays();
    void setupVoxelZLayerVboData();
    void setupSamplerObject();
    void setupTransformFeedback();
    void generateTriTableTexture();
    void setupVaoForIsoSurfaceTriangles();
    void setupVoxelEdgesVao();
    void setupVoxelEdgesVertexBuffer();

    void updateShaderUniforms(const Synergy::Camera &camera);

    void generateIsoSurfaceTriangles(
            GLuint volumeData_texture3d,
            float isoSurfaceThreshold
    );

    void renderIsoSurface(const Synergy::Camera &camera);

    void renderVoxelEdges(const Synergy::Camera &camera);


    // TODO Dustin - remove after testing:
    void inspectTransformFeedbackBuffer();

};
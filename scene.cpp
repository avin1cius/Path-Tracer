#include "scene.h"

Scene::Scene( void )
{}

Scene::~Scene( void )
{}

bool Scene::intersect( const Ray &ray,
                       IntersectionRecord &intersection_record ) const
{
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    std::size_t num_primitives = primitives_.size();

    // Loops over the list of primitives, testing the intersection of each primitive against the given ray 
    for ( std::size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++ )
        if ( primitives_[primitive_id]->intersect( ray, tmp_intersection_record ) )
            if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) )
            {
                intersection_record = tmp_intersection_record;
                intersection_result = true; // the ray intersects a primitive!
            }

    return intersection_result;
}

void Scene::load( void ) 
{
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ 
        glm::vec3{ 0.0f, 0.0f, 5.0f }, 0.5f, glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 20.0f, 20.0f, 20.f }}));
/*    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f,-1.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f,-1.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f,-0.5f,-1.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.5f,-2.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f,-2.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f,-2.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f,-0.5f,-2.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.5f,-3.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f,-3.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f,-3.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f,-0.5f,-3.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.5f,-4.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f,-4.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f,-4.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f,-0.5f,-4.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.5f,-5.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f,-5.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f,-5.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f,-0.5f,-5.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );

*/
    //fundo
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ 
        glm::vec3{-3.0f, 3.0f,-4.0f}, glm::vec3{ 3.0f, 3.0f,-4.0f}, glm::vec3{ 3.0f,-3.0f,-4.0f}, glm::vec3{ 0.9f,0.89f,0.24f}, glm::vec3{ 0.0f, 0.0f, 0.0f }}));
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{-3.0f, 3.0f,-4.0f}, glm::vec3{-3.0f,-3.0f,-4.0f}, glm::vec3{ 3.0f,-3.0f,-4.0f}, glm::vec3{ 0.9f,0.89f,0.24f}, glm::vec3{ 0.0f, 0.0f, 0.0f }}));    
    //parede direita                                                                        
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{ 3.0f, 3.0f, 5.0f}, glm::vec3{ 3.0f, 3.0f,-4.0f}, glm::vec3{ 3.0f,-3.0f,-4.0f}, glm::vec3{ 0.0f, 1.0f, 0.0f}, glm::vec3{ 0.0f, 0.0f, 0.0f }}));
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{ 3.0f, 3.0f, 5.0f}, glm::vec3{ 3.0f,-3.0f, 5.0f}, glm::vec3{ 3.0f,-3.0f,-4.0f}, glm::vec3{ 0.0f, 1.0f, 0.0f}, glm::vec3{ 0.0f, 0.0f, 0.0f }}));  
    //parede esquerda
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{-3.0f, 3.0f, 5.0f}, glm::vec3{-3.0f, 3.0f,-4.0f}, glm::vec3{-3.0f,-3.0f,-4.0f}, glm::vec3{ 1.0f, 0.0f, 0.0f}, glm::vec3{ 0.0f, 0.0f, 0.0f }}));
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{-3.0f, 3.0f, 5.0f}, glm::vec3{-3.0f,-3.0f, 5.0f}, glm::vec3{-3.0f,-3.0f,-4.0f}, glm::vec3{ 1.0f, 0.0f, 0.0f}, glm::vec3{ 0.0f, 0.0f, 0.0f }}));       
    //teto
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{-3.0f, 3.0f,-4.0f}, glm::vec3{-3.0f, 3.0f, 4.0f}, glm::vec3{ 3.0f, 3.0f, 4.0f}, glm::vec3{ 0.9f,0.89f,0.24f}, glm::vec3{ 0.0f, 0.0f, 0.0f }}));
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{-3.0f, 3.0f,-4.0f}, glm::vec3{ 3.0f, 3.0f, 4.0f}, glm::vec3{ 3.0f, 3.0f,-4.0f}, glm::vec3{ 0.9f,0.89f,0.24f}, glm::vec3{ 0.0f, 0.0f, 0.0f }}));                                                                       
    //chao
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{-3.0f,-3.0f,-4.0f}, glm::vec3{ 3.0f,-3.0f,-4.0f}, glm::vec3{-3.0f,-3.0f, 4.0f}, glm::vec3{ 0.2f, 0.2f, 0.2f}, glm::vec3{ 0.0f, 0.0f, 0.0f }}));
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{ 3.0f,-3.0f,-4.0f}, glm::vec3{ 3.0f,-3.0f, 4.0f}, glm::vec3{-3.0f,-3.0f, 4.0f}, glm::vec3{ 0.2f, 0.2f, 0.2f}, glm::vec3{ 0.0f, 0.0f, 0.0f }})); 
}

void Scene::loadObject(const char * obj)
{
    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(obj, aiProcess_Triangulate);

    unsigned int mesh, face;

    srand(std::time(0));

    for (mesh = 0 ; mesh < scene->mNumMeshes; mesh++) 
    {
        aiColor3D brdf = {0,0,0};
        aiColor3D emittance = {0,0,0};
        
        if (scene->mMaterials) {
            // Setting up the BRDF and emitance of the mesh
            scene->mMaterials[scene->mMeshes[mesh]->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, brdf);
            scene->mMaterials[scene->mMeshes[mesh]->mMaterialIndex]->Get(AI_MATKEY_COLOR_EMISSIVE, emittance);
        }
    
        for(face = 0; face < scene->mMeshes[mesh]->mNumFaces; face++)
        {
            //float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            //float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            //float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

            primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ 
                glm::vec3 { (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x, 
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y, 
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z},
                                                                                      
                glm::vec3 { (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z},

                glm::vec3 { (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y,
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z},
                                                                                                                                                                                 
                glm::vec3 { brdf.r, brdf.g, brdf.b },
                glm::vec3 { emittance.r, emittance.g, emittance.b }})); 
        }
    }
}


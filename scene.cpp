#include "scene.h"

Scene::Scene( void )
{}

Scene::~Scene( void )
{
    if ( bvh_ )
    {
        delete bvh_;
        bvh_ = nullptr;
    }
}
/*
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
*/
bool Scene::intersect( const Ray &ray,
                       IntersectionRecord &intersection_record ) const
{
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    std::size_t num_primitives = primitives_.size();

    switch( acceleration_structure_ )
    {
        case AccelerationStructure::NONE:
            for ( std::size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++ )
            {
                if ( primitives_[primitive_id]->intersect( ray, tmp_intersection_record ) )
                {
                    if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) )
                    {
                        intersection_record = tmp_intersection_record;
                        intersection_result = true;
                    }
                }
            }
            break;

        case AccelerationStructure::BVH_SAH:
            intersection_result = bvh_->intersect( ray, intersection_record);
            break;
    }

    return intersection_result;
}

void Scene::buildAccelerationStructure( void )
{
    if ( acceleration_structure_ == Scene::AccelerationStructure::BVH_SAH )
    {
        buildBVH();
        std::clog << std::endl;
    }
}

void Scene::buildBVH( void )
{
    bvh_ = new BVH( primitives_ );
}

void Scene::load( void ) 
{
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ 
        glm::vec3{ 4.0f, 4.0f, 2.0f }, 0.8f, glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 10.0f, 10.0f, 10.0f }, false, false, false}));

    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ 
        glm::vec3{ 0.0f, 0.0f, 0.0f }, 1.0f, glm::vec3{ 1.0f, 0.71f, 0.29f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, false, false, true}));    


    //left
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ 
        glm::vec3{-1.2f,-1.0f,-1.5f}, glm::vec3{ -1.2f, -1.0f, 20.0f}, glm::vec3{ -1.2f,20.0f,-1.5f}, glm::vec3{ 0.75f,0.25f,0.25f}, glm::vec3{ 0.0f, 0.0f, 0.0f }, false, false, false}));
    //ground
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{-1.2f,-1.0f,-1.5f}, glm::vec3{-1.2f, -1.0f, 20.0f}, glm::vec3{ 20.0f,-1.0f,-1.5f}, glm::vec3{ 1.0f,1.0f,1.0f}, glm::vec3{ 0.0f, 0.0f, 0.0f }, false, false, false}));    
    //back                                                                        
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{-1.2f,-1.0f,-1.5f}, glm::vec3{ 20.0f, -1.0f,-1.5f}, glm::vec3{ -1.2f,20.0f,-1.5f}, glm::vec3{ 1.0f, 1.0f, 1.0f}, glm::vec3{ 0.0f, 0.0f, 0.0f },false, false, false}));
 
  
 /*   primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
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
*/
}

void Scene::loadObject(const char * obj)
{
    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(obj, aiProcess_Triangulate);

    unsigned int mesh, face;

    float s = 6.0f;
    float t_y = -0.9f;

    //srand(std::time(0));

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
                glm::vec3 { (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x*s, 
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y*s + t_y, 
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z*s},
                                                                                      
                glm::vec3 { (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x*s,
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y*s + t_y,
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z*s},

                glm::vec3 { (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x*s,
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y*s + t_y,
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z*s},
                                                                                                                                                                                 
                glm::vec3 { 0.5334f, 0.84f, 0.886f},//brdf.r, brdf.g, brdf.b },
                glm::vec3 { emittance.r, emittance.g, emittance.b },false, false, false})); 
        }
    }
}


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
    //ceiling light 1
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ 
        glm::vec3{-1.0f,4.95f,4.5f}, glm::vec3{ -1.0f, 4.95f, 5.5f}, glm::vec3{ 1.0f,4.95f,4.5f}, glm::vec3{ 0.75f,0.75f,0.75f}, glm::vec3{ 7.0f, 7.0f, 7.0f }, false, false, false}));
    //ceiling light 1
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ 
        glm::vec3{1.0f,4.95f,5.5f}, glm::vec3{ 1.0f, 4.95f, 5.5f}, glm::vec3{ 1.0f,4.95f,4.5f}, glm::vec3{ 0.75f,0.75f,0.75f}, glm::vec3{ 7.0f, 7.0f, 7.0f }, false, false, false}));
  
    //front triangle
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ 
        glm::vec3{-1.2f,0.0f,1.5f}, glm::vec3{ 1.2f, 0.0f, 1.5f}, glm::vec3{ 0.0f,2.4f,1.5f}, glm::vec3{ 0.17f, 0.17f, 0.17f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, false, false, false}));
    //ground1
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{5.0f,0.0f,0.0f}, glm::vec3{-5.0f, 0.0f, 0.0f}, glm::vec3{ -5.0f,0.0f,10.0f}, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, false, false, false}));    
    //ground2                                                                        
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{5.0f,0.0f,0.0f}, glm::vec3{ -5.0f, 0.0f,10.0f}, glm::vec3{ 5.0f,0.0f,10.0f}, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f },false, false, false}));
 
    //groundfront                                                                        
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{5.0f,0.0f,0.0f}, glm::vec3{ -5.0f, 0.0f,0.0f}, glm::vec3{ 0.0f,0.0f,-5.0f}, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f },false, false, false}));
    
    //mirror left 1                                                                        
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{0.0f,0.0f,-5.0f}, glm::vec3{ 0.0f, 5.0f,-5.0f}, glm::vec3{ -5.0f,0.0f,0.0f}, glm::vec3{ 0.75f,0.75f,0.75f }, glm::vec3{ 0.0f, 0.0f, 0.0f },true, false, false}));

    //mirror left 2                                                                        
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{-5.0f,5.0f,0.0f}, glm::vec3{ 0.0f, 5.0f,-5.0f}, glm::vec3{ -5.0f,0.0f,0.0f}, glm::vec3{ 0.75f,0.75f,0.75f }, glm::vec3{ 0.0f, 0.0f, 0.0f },true, false, false}));
    
    //mirror right 1                                                                        
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{0.0f,0.0f,-5.0f}, glm::vec3{ 0.0f, 5.0f,-5.0f}, glm::vec3{ 5.0f,0.0f,0.0f}, glm::vec3{ 0.75f,0.75f,0.75f }, glm::vec3{ 0.0f, 0.0f, 0.0f },true, false, false}));
    
    //mirror right 2                                                                        
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{5.0f,5.0f,0.0f}, glm::vec3{ 0.0f, 5.0f,-5.0f}, glm::vec3{ 5.0f,0.0f,0.0f}, glm::vec3{ 0.75f,0.75f,0.75f }, glm::vec3{ 0.0f, 0.0f, 0.0f },true, false, false}));

    //ceiling front                                                                        
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{5.0f,5.0f,0.0f}, glm::vec3{ -5.0f, 5.0f,0.0f}, glm::vec3{ 0.0f,5.0f,-5.0f}, glm::vec3{ 0.968f, 0.086f, 0.086f }, glm::vec3{ 0.0f, 0.0f, 0.0f },false, false, false}));

    //ceiling1
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{5.0f,5.0f,0.0f}, glm::vec3{-5.0f, 5.0f, 0.0f}, glm::vec3{ -5.0f,5.0f,10.0f}, glm::vec3{ 0.968f, 0.086f, 0.086f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, false, false, false}));    
    //ceiling2                                                                        
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{5.0f,5.0f,0.0f}, glm::vec3{ -5.0f, 5.0f,10.0f}, glm::vec3{ 5.0f,5.0f,10.0f}, glm::vec3{ 0.968f, 0.086f, 0.086f }, glm::vec3{ 0.0f, 0.0f, 0.0f },false, false, false}));
    
    //left wall 1
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{-5.0f,0.0f,0.0f}, glm::vec3{-5.0f, 5.0f, 0.0f}, glm::vec3{ -5.0f,0.0f,10.0f}, glm::vec3{ 0.75f,0.75f,0.75f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, false, false, false}));

    //left wall 2
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{-5.0f,5.0f,0.0f}, glm::vec3{-5.0f, 5.0f, 10.0f}, glm::vec3{ -5.0f,0.0f,10.0f}, glm::vec3{ 0.75f,0.75f,0.75f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, false, false, false}));
 
    //right wall 1
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{5.0f,0.0f,0.0f}, glm::vec3{5.0f, 5.0f, 0.0f}, glm::vec3{ 5.0f,0.0f,10.0f}, glm::vec3{ 0.75f,0.75f,0.75f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, false, false, false}));

    //right wall 2
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{5.0f,5.0f,0.0f}, glm::vec3{5.0f, 5.0f, 10.0f}, glm::vec3{ 5.0f,0.0f,10.0f}, glm::vec3{ 0.75f,0.75f,0.75f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, false, false, false}));

    //back wall 1
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{-5.0f,0.0f,10.0f}, glm::vec3{-5.0f, 5.0f, 10.0f}, glm::vec3{ 5.0f,0.0f,10.0f}, glm::vec3{ 0.75f,0.75f,0.75f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, false, false, false}));

    //back wall 2
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{
        glm::vec3{5.0f,5.0f,10.0f}, glm::vec3{-5.0f, 5.0f, 10.0f}, glm::vec3{ 5.0f,0.0f,10.0f}, glm::vec3{ 0.75f,0.75f,0.75f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, false, false, false}));
}

void Scene::loadObject(const char * obj)
{
    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(obj, aiProcess_Triangulate);

    unsigned int mesh, face;

    float s = 0.8f;
    float t_y = 0.0f;
    float t_x = 0.0f;
    float t_z = 0.0f;

    //srand(std::time(0));

    for (mesh = 0 ; mesh < scene->mNumMeshes; mesh++) 
    {
        aiColor3D brdf = {0,0,0};
        aiColor3D emittance = {0.0f,0.0f,0.0f};
        
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

            glm::vec3 p1 = { (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x, 
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y, 
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z};
            p1 = p1*s;           

            glm::vec3 p2 = { (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z};            
            p2 = p2 * s;

            glm::vec3 p3 = { (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y,
                            (float)scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z};
            p3 = p3 * s;

            primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ p1, p2, p3,                                                                                                                                                              
                glm::vec3 { 1.00f, 0.71f, 0.29f},//brdf.r, brdf.g, brdf.b },
                glm::vec3 { emittance.r, emittance.g, emittance.b },false, false, true})); 
        }
    }
}

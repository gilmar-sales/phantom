#pragma once

#include <glm/glm.hpp>

PH_NAMESPACE_BEGIN

struct MeshComponent
{
    uint32_t vertex_array_object;
    uint32_t vertex_buffer_object;
    uint32_t element_buffer_object;
    uint32_t index_count;


    MeshComponent() = default;
    MeshComponent(const MeshComponent&) = default;
    MeshComponent(
        const uint32_t vertex_array_object,
        const uint32_t vertex_buffer_object,
        const uint32_t element_buffer_object
        )
        :   vertex_array_object(vertex_array_object),
            vertex_buffer_object(vertex_buffer_object),
            element_buffer_object(element_buffer_object)
        {}
};

PH_NAMESPACE_END

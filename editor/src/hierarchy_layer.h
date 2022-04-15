//
// Created by gilmar on 30/03/2022.
//

#ifndef EDITOR_HIERARCHY_LAYER_H
#define EDITOR_HIERARCHY_LAYER_H

#include <core/layer.h>
#include <scene/scene.h>

PH_NAMESPACE_BEGIN

class HierarchyLayer : public Layer
{
public:
    HierarchyLayer(shared<Scene> scene);
    ~HierarchyLayer() override = default;

    void draw_entity_node(unsigned entity);
    void draw_components();
    void add_mesh(unsigned entity);

    void on_update() override;
    void on_gui_render() override;
private:
    shared<Scene> scene;
    unsigned selectionContext;
    unsigned nodeToRename;
};

PH_NAMESPACE_END

#endif //EDITOR_HIERARCHY_LAYER_H

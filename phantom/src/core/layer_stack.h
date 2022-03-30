#pragma once

#include <vector>

#include "layer.h"

PH_NAMESPACE_BEGIN

class LayerStack
{
private:
    std::vector<Layer*> m_layers;
    unsigned m_last_index;
public:
    LayerStack() = default;
    ~LayerStack();

    void push_layer(Layer* layer);
    void push_overlay(Layer* layer);
    void pop_layer(Layer* layer);
    void pop_overlay(Layer* layer);

    std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
    std::vector<Layer*>::iterator end() { return m_layers.end(); }
    std::vector<Layer*>::reverse_iterator rbegin() { return m_layers.rbegin(); }
    std::vector<Layer*>::reverse_iterator rend() { return m_layers.rend(); }

    std::vector<Layer*>::const_iterator begin() const { return m_layers.begin(); }
    std::vector<Layer*>::const_iterator end()	const { return m_layers.end(); }
    std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_layers.rbegin(); }
    std::vector<Layer*>::const_reverse_iterator rend() const { return m_layers.rend(); }
};

PH_NAMESPACE_END

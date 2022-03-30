#include "layer_stack.h"

PH_NAMESPACE_BEGIN

LayerStack::~LayerStack()
{
	for (Layer* layer : m_layers)
	{
		layer->on_detach();
		delete layer;
	}
}

void LayerStack::push_layer(Layer* layer)
{
	m_layers.emplace(m_layers.begin() + m_last_index, layer);
	m_last_index++;
}
void LayerStack::push_overlay(Layer* layer)
{
	m_layers.emplace_back(layer);
}

void LayerStack::pop_layer(Layer* layer)
{
	auto it = std::find(m_layers.begin(), m_layers.begin() + m_last_index, layer);
	if (it != m_layers.begin() + m_last_index)
	{
		layer->on_detach();
		m_layers.erase(it);
		m_last_index--;
	}
}

void LayerStack::pop_overlay(Layer* layer)
{

	auto it = std::find(m_layers.begin() + m_last_index, m_layers.end(), layer);
	if (it != m_layers.begin() + m_last_index)
	{
		layer->on_detach();
		m_layers.erase(it);
		m_last_index--;
	}
}
	
PH_NAMESPACE_END
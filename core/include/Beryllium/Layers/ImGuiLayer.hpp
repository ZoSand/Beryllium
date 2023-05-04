#ifndef BE_IMGUI_LAYER_HPP
#define BE_IMGUI_LAYER_HPP

#	include <Beryllium/Layer.hpp>

namespace Beryllium
{
	class BE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual bool OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block);

		void SetDarkThemeColors();

		uint32_t GetActiveWidgetID() const;
	private:
		bool m_BlockEvents = true;
	};
}
#endif // ifndef  

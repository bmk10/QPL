#include <qpl/QSF/framework.hpp>

#ifdef QPL_USE_SFML

namespace qsf {
	bool qsf::event_info::key_pressed(sf::Keyboard::Key key) const {
		return this->m_keys_pressed.find(key) != this->m_keys_pressed.cend();
	}
	bool qsf::event_info::keys_pressed(const std::vector<sf::Keyboard::Key>& keys) const {
		for (auto& i : keys) {
			if (this->m_keys_pressed.find(i) == this->m_keys_pressed.cend()) {
				return false;
			}
		}
		return true;
	}
	bool qsf::event_info::key_released(sf::Keyboard::Key key) const {
		return this->m_keys_released.find(key) != this->m_keys_released.cend();
	}
	bool qsf::event_info::keys_released(const std::vector<sf::Keyboard::Key>& keys) const {
		for (auto& i : keys) {
			if (this->m_keys_released.find(i) == this->m_keys_released.cend()) {
				return false;
			}
		}
		return true;
	}
	bool qsf::event_info::key_holding(sf::Keyboard::Key key) const {
		return this->m_keys_holding.find(key) != this->m_keys_holding.cend();
	}
	bool qsf::event_info::keys_holding(const std::vector<sf::Keyboard::Key>& keys) const {
		for (auto& i : keys) {
			if (this->m_keys_holding.find(i) == this->m_keys_holding.cend()) {
				return false;
			}
		}
		return true;
	}

	bool qsf::event_info::left_mouse_clicked() const {
		return this->m_left_mouse_clicked;
	}
	bool qsf::event_info::left_mouse_released() const {
		return this->m_left_mouse_released;
	}
	bool qsf::event_info::right_mouse_clicked() const {
		return this->m_right_mouse_clicked;
	}
	bool qsf::event_info::right_mouse_released() const {
		return this->m_right_mouse_released;
	}
	bool qsf::event_info::scrolled_up() const {
		return this->m_scrolled_up;
	}
	bool qsf::event_info::scrolled_down() const {
		return this->m_scrolled_down;
	}
	bool qsf::event_info::key_pressed() const {
		return this->m_key_pressed;
	}
	bool qsf::event_info::key_released() const {
		return this->m_key_released;
	}
	bool qsf::event_info::key_holding() const {
		return this->m_key_holding;
	}

	bool qsf::event_info::resized() const {
		return this->m_resized;
	}
	bool qsf::event_info::window_closed() const {
		return this->m_window_closed;
	}

	bool qsf::event_info::holding_left_mouse() const {
		return this->m_holding_left_mouse;
	}
	bool qsf::event_info::holding_right_mouse() const {
		return this->m_holding_right_mouse;
	}
	bool qsf::event_info::holding_key() const {
		return this->m_holding_key;
	}

	qsf::vector2i qsf::event_info::resized_size() const {
		return this->m_resized_size;
	}

	qsf::vector2i qsf::event_info::mouse_position() const {
		return this->m_mouse_position;
	}

	void qsf::base_state::clear() {
		this->framework->window.clear(this->clear_color);
	}
	void qsf::base_state::update_on_resize() {

	}
	void qsf::base_state::draw(const sf::Drawable& drawable, sf::RenderStates states) {
		this->framework->window.draw(drawable, states);
	}
	void qsf::base_state::event_update() {
		sf::Event event;

		this->event.m_left_mouse_clicked = false;
		this->event.m_left_mouse_released = false;
		this->event.m_right_mouse_clicked = false;
		this->event.m_right_mouse_released = false;
		this->event.m_scrolled_up = false;
		this->event.m_scrolled_down = false;
		this->event.m_key_pressed = false;
		this->event.m_key_released = false;
		this->event.m_mouse_moved = false;
		this->event.m_key_holding = false;
		this->event.m_window_closed = false;
		this->event.m_resized = false;

		this->event.m_keys_pressed.clear();
		this->event.m_keys_released.clear();

		while (this->framework->window.pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					this->event.m_left_mouse_clicked = true;
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					this->event.m_right_mouse_clicked = true;
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					this->event.m_left_mouse_released = true;
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					this->event.m_right_mouse_released = true;
				}
			}
			else if (event.type == sf::Event::KeyPressed) {
				this->event.m_keys_pressed.insert(event.key.code);
				this->event.m_keys_holding.insert(event.key.code);
			}
			else if (event.type == sf::Event::KeyReleased) {
				this->event.m_keys_released.insert(event.key.code);
				this->event.m_keys_holding.erase(event.key.code);
			}
			else if (event.type == sf::Event::MouseWheelMoved) {
				if (event.mouseWheel.delta < 0) {
					this->event.m_scrolled_down = true;
				}
				if (event.mouseWheel.delta > 0) {
					this->event.m_scrolled_up = true;
				}
			}
			else if (event.type == sf::Event::Closed) {
				this->event.m_window_closed = true;
			}
			else if (event.type == sf::Event::MouseMoved) {
				this->event.m_mouse_moved = true;
			}
			else if (event.type == sf::Event::Resized) {
				this->event.m_resized = true;
				this->event.m_resized_size = {event.size.width, event.size.height};
			}
		}
		this->event.m_mouse_position = sf::Mouse::getPosition(this->framework->window);
	}
	void qsf::base_state::update_close_window() {
		if (this->event.window_closed()) {
			this->framework->window.close();
		}
	}
	void qsf::base_state::hide_cursor(){
		this->framework->hide_cursor();
	}
	void qsf::base_state::show_cursor() {
		this->framework->show_cursor();
	}
	void qsf::base_state::set_cursor_position(qsf::vector2i position) {
		this->framework->set_cursor_position(position);
	}
	qsf::vector2i qsf::base_state::dimension() const {
		return this->framework->m_dimension;
	}
	void qsf::base_state::set_graph_color(qsf::rgb color) {
		this->framework->set_graph_color(color);
	}
	void qsf::base_state::set_graph_thickness(qpl::f64 thickness) {
		this->framework->set_graph_thickness(thickness);
	}
	void qsf::base_state::set_graph_interpolation_steps(qpl::size interpolation_steps) {
		this->framework->set_graph_interpolation_steps(interpolation_steps);
	}
	void qsf::base_state::set_graph_color(qsf::rgb color, const std::string& name) {
		this->framework->set_graph_color(color, name);
	}
	void qsf::base_state::set_graph_thickness(qpl::f64 thickness, const std::string& name) {
		this->framework->set_graph_thickness(thickness, name);
	}
	void qsf::base_state::set_graph_interpolation_steps(qpl::size interpolation_steps, const std::string& name) {
		this->framework->set_graph_interpolation_steps(interpolation_steps, name);
	}
	void qsf::base_state::set_graph_dimension(qsf::vector2f dimension) {
		this->framework->set_graph_dimension(dimension);
	}
	void qsf::base_state::set_graph_position(qsf::vector2f position) {
		this->framework->set_graph_position(position);
	}
	void qsf::base_state::pop_this_state() {
		this->m_pop_this_state = true;
	}
	qpl::f64 qsf::base_state::frame_time() const {
		return this->framework->frame_time();
	}

	void qsf::framework::gameloop() {
		if (!this->is_created()) {
			this->create();
		}

		while (this->window.isOpen()) {
			this->m_frametime = this->m_frametime_clock.elapsed_f_reset();

			this->states.back()->event_update();

			if (this->states.back()->event.resized()) {
				auto new_dimension = this->states.back()->event.resized_size();
				sf::FloatRect view(0.0f, 0.0f, static_cast<float>(new_dimension.x), static_cast<float>(new_dimension.y));
				this->window.setView(sf::View(view));
				this->m_dimension = new_dimension;
				this->states.back()->update_on_resize();
			}
			this->states.back()->updating();
			this->states.back()->update_close_window();

			if (this->states.back()->m_pop_this_state) {
				this->states.pop_back();
				if (this->states.empty()) {
					break;
				}
			}
			this->states.back()->clear();
			this->states.back()->drawing();
			this->window.display();
		}
	}
	void qsf::framework::set_graph_axis_font(const std::string& font_name) {
		qsf::drawing_graph.y_axis_text.font_name = font_name;
	}
	void qsf::framework::set_graph_color(qsf::rgb color, const std::string& name) {
		qsf::drawing_graph[name].color = color;
	}
	void qsf::framework::set_graph_thickness(qpl::f64 thickness, const std::string& name) {
		qsf::drawing_graph[name].thickness = thickness;
	}
	void qsf::framework::set_graph_interpolation_steps(qpl::size interpolation_steps, const std::string& name) {
		qsf::drawing_graph[name].interpolation_steps = interpolation_steps;
	}
	void qsf::framework::set_graph_color(qsf::rgb color) {
		qsf::drawing_graph.color = color;
	}
	void qsf::framework::set_graph_thickness(qpl::f64 thickness) {
		qsf::drawing_graph.thickness = thickness;
	}
	void qsf::framework::set_graph_interpolation_steps(qpl::size interpolation_steps) {
		qsf::drawing_graph.interpolation_steps = interpolation_steps;
	}
	void qsf::framework::set_graph_dimension(qsf::vector2f dimension) {
		qsf::drawing_graph.hitbox.dimension = dimension;
	}
	void qsf::framework::set_graph_position(qsf::vector2f position) {
		qsf::drawing_graph.hitbox.position = position;
	}
	qpl::f64 qsf::framework::frame_time() const {
		return this->m_frametime;
	}

	void qsf::framework::create() {
		if (!this->is_created()) {
			sf::ContextSettings settings;
			settings.antialiasingLevel = 12;

			this->window.create(sf::VideoMode({ this->m_dimension.x, this->m_dimension.y }), this->m_title, this->m_style, settings);
			this->m_created = true;
		}
	}
	bool qsf::framework::is_created() const {
		return this->m_created;
	}
	void qsf::framework::set_info(const std::string& title, qsf::vector2u dimension, qpl::u32 style) {
		this->set_title(title);
		this->set_dimension(dimension);
		this->set_style(style);
	}
	void qsf::framework::set_title(const std::string& title) {
		this->m_title = title;
	}
	void qsf::framework::set_dimension(qsf::vector2u dimension) {
		this->m_dimension = dimension;
	}
	void qsf::framework::set_style(qpl::u32 style) {
		this->m_style = style;
	}
	void qsf::framework::hide_cursor() {
		this->window.setMouseCursorVisible(false);
		//todo
	}
	void qsf::framework::show_cursor() {
		this->window.setMouseCursorVisible(true);
		//todo
	}
	void qsf::framework::set_cursor_position(qsf::vector2i position) {
		//todo
	}
}

#endif
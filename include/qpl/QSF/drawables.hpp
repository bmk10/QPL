#ifndef QPLSF_DRAWABLES_HPP
#define QPLSF_DRAWABLES_HPP
#pragma once

#if defined(QPL_USE_SFML) || defined(QPL_USE_ALL)
#include <qpl/qpldeclspec.hpp>
#include <qpl/QSF/vector.hpp>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <qpl/QSF/color.hpp>
#include <qpl/string.hpp>
#include <functional>
#include <string>


namespace qsf {
	struct vtext;
	struct text;
	struct vrectangle;
	struct rectangle;
	struct vrectangles;
	struct rectangles;
	struct vpoint;
	struct point;
	struct vpoints;
	struct points;
	struct vcircle;
	struct circle;
	struct vcircles;
	struct circles;
	struct vline;
	struct line;
	struct vlines;
	struct lines;
	struct vthick_line;
	struct thick_line;
	struct vthick_lines;
	struct thick_lines;
	struct vgraph;
	struct graph;
	struct vbutton;
	struct button;

	struct event_info;

	QPLDLL qsf::vrectangle text_hitbox(const sf::Text& text);
	QPLDLL qsf::vrectangle text_hitbox(const qsf::text& text);
	QPLDLL void centerize_text(sf::Text& text);
	QPLDLL void centerize_text(qsf::text& text);

	namespace detail {
		QPLDLL extern qsf::text text;
		QPLDLL extern qsf::rectangle rectangle;
		QPLDLL extern qsf::rectangles rectangles;
		QPLDLL extern qsf::point point;
		QPLDLL extern qsf::points points;
		QPLDLL extern qsf::circle circle;
		QPLDLL extern qsf::circles circles;
		QPLDLL extern qsf::line line;
		QPLDLL extern qsf::lines lines;
		QPLDLL extern qsf::thick_line thick_line;
		QPLDLL extern qsf::thick_lines thick_lines;
		QPLDLL extern qsf::graph graph;
		QPLDLL extern qsf::button button;
	}
	QPLDLL extern qsf::vgraph drawing_graph;

	struct vertex {
		vertex() {

		}
		vertex(qsf::vector2f position, qsf::rgb color) {
			this->position = position;
			this->color = color;
		}

		qsf::vector2f position;
		qsf::rgb color;
		qsf::vector2f tex_coords;

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
	};

	enum class primitive_type {
		points,        
		lines,         
		line_strip,    
		triangles,     
		triangle_strip,
		triangle_fan,  
		quads,         
	};

	struct vertex_array {

		QPLDLL void set_primitive_type(qsf::primitive_type primitive_type);

		QPLDLL qpl::size size() const;
		QPLDLL void resize(qpl::size new_size);
		QPLDLL void reserve(qpl::size new_size);

		QPLDLL void add(const qsf::vertex& vertex);

		QPLDLL void clear();

		QPLDLL qsf::vertex& operator[](qpl::u32 index);
		QPLDLL const qsf::vertex& operator[](qpl::u32 index) const;

		QPLDLL qsf::vertex& front();
		QPLDLL const qsf::vertex& front() const;

		QPLDLL qsf::vertex& back();
		QPLDLL const qsf::vertex& back() const;

		QPLDLL std::vector<qsf::vertex>::iterator begin();
		QPLDLL std::vector<qsf::vertex>::const_iterator begin() const;
		QPLDLL std::vector<qsf::vertex>::const_iterator cbegin() const;

		QPLDLL std::vector<qsf::vertex>::iterator end();
		QPLDLL std::vector<qsf::vertex>::const_iterator end() const;
		QPLDLL std::vector<qsf::vertex>::const_iterator cend() const;

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		std::vector<qsf::vertex> vertices;
		qsf::primitive_type primitive_type;
	};

	struct vtext {
		QPLDLL void set_font(const std::string& font_name);
		QPLDLL void set_style(qpl::u32 style);
		QPLDLL void set_character_size(qpl::u32 character_size);
		QPLDLL void set_color(qsf::rgb color);
		QPLDLL void set_outline_thickness(qpl::f32 outline_thickness);
		QPLDLL void set_outline_color(qsf::rgb color);
		QPLDLL void set_letter_spacing(qpl::f32 spacing);
		QPLDLL void set_position(qsf::vector2f position);
		QPLDLL void set_string(const std::string& string);
		QPLDLL bool operator==(const vtext& other) const;


		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		std::string font_name;
		qpl::u32 style = sf::Text::Style::Regular;
		qpl::u32 character_size = 15u;
		qsf::rgb color = qsf::rgb::black;
		qpl::f32 outline_thickness;
		qsf::rgb outline_color;
		qpl::f32 letter_spacing;
		qsf::vector2f position;
		std::string string;
	};

	struct text {
		QPLDLL std::string get_font() const;
		QPLDLL void set_font(const std::string& font_name);
		QPLDLL void set_style(qpl::u32 style);
		QPLDLL void set_character_size(qpl::u32 character_size);
		QPLDLL void set_color(qsf::rgb color);
		QPLDLL void set_outline_thickness(qpl::f32 outline_thickness);
		QPLDLL void set_outline_color(qsf::rgb color);
		QPLDLL void set_letter_spacing(qpl::f32 spacing);
		QPLDLL void set_position(qsf::vector2f position);
		QPLDLL void set_center(qsf::vector2f position);
		QPLDLL void set_string(const std::string& string);
		QPLDLL void centerize();
		QPLDLL void centerize_x();
		QPLDLL void centerize_y();

		qsf::text() {

		}
		qsf::text(const qsf::vtext& other) {
			*this = other;
		}

		QPLDLL qsf::vrectangle hitbox() const;
		

		QPLDLL std::string string() const;
		QPLDLL void clear();
		QPLDLL qsf::text& operator<<(const std::string& string);

		QPLDLL qsf::text& operator=(const qsf::vtext& text);

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;


		std::string m_font;
		std::string m_string;
		sf::Text m_text;
	};


	struct vrectangle {
		vrectangle() {

		}
		vrectangle(qsf::vector2f position, qsf::vector2f dimension) {
			this->position = position;
			this->dimension = dimension;
		}
		vrectangle(qsf::vector2f position, qsf::vector2f dimension, qsf::rgb color) {
			this->position = position;
			this->dimension = dimension;
			this->color = color;
		}

		QPLDLL void set_dimension(qsf::vector2f dimension);
		QPLDLL void set_position(qsf::vector2f position);
		QPLDLL void set_center(qsf::vector2f position);
		QPLDLL void set_color(qsf::rgb color);
		QPLDLL void set_outline_thickness(qpl::f32 outline_thickness);
		QPLDLL void set_outline_color(qsf::rgb outline_color);

		QPLDLL qsf::vector2f get_dimension() const;
		QPLDLL qsf::vector2f get_position() const;
		QPLDLL qsf::vector2f get_center() const;
		QPLDLL qsf::rgb get_color() const;
		QPLDLL qpl::f32 get_outline_thickness() const;
		QPLDLL qsf::rgb get_outline_color() const;

		QPLDLL std::string string() const;

		QPLDLL void increase(qpl::f32 delta);
		QPLDLL qsf::vrectangle increased(qpl::f32 delta) const;

		QPLDLL bool contains(qsf::vector2f position) const;


		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		qsf::vector2f dimension;
		qsf::vector2f position;
		qsf::rgb color;
		qpl::f32 outline_thickness;
		qsf::rgb outline_color;
	};

	struct rectangle {
		QPLDLL void set_dimension(qsf::vector2f dimension);
		QPLDLL void set_position(qsf::vector2f position);
		QPLDLL void set_center(qsf::vector2f position);
		QPLDLL void set_color(qsf::rgb color);
		QPLDLL void set_outline_thickness(qpl::f32 outline_thickness);
		QPLDLL void set_outline_color(qsf::rgb outline_color);

		QPLDLL bool contains(qsf::vector2f position) const;

		QPLDLL qsf::vector2f get_position() const;
		QPLDLL qsf::vector2f get_dimension() const;
		QPLDLL qsf::rgb get_color() const;

		QPLDLL qsf::vlines as_lines() const;
		QPLDLL qsf::vlines as_lines_completed() const;

		QPLDLL qsf::vector2f center() const;

		QPLDLL qsf::rectangle& operator=(const qsf::vrectangle& rectangle);

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		sf::RectangleShape m_rect;
	};

	struct vrectangles {
		QPLDLL qpl::size size() const;
		QPLDLL void resize(qpl::size new_size);
		QPLDLL void reserve(qpl::size new_size);
		QPLDLL void clear();
		QPLDLL void add(const qsf::vrectangle& rect);

		QPLDLL qsf::vrectangle& operator[](qpl::u32 index);
		QPLDLL const qsf::vrectangle& operator[](qpl::u32 index) const;

		QPLDLL qsf::vrectangle& front();
		QPLDLL const qsf::vrectangle& front() const;

		QPLDLL qsf::vrectangle& back();
		QPLDLL const qsf::vrectangle& back() const;

		QPLDLL std::vector<qsf::vrectangle>::iterator begin();
		QPLDLL std::vector<qsf::vrectangle>::const_iterator begin() const;
		QPLDLL std::vector<qsf::vrectangle>::const_iterator cbegin() const;

		QPLDLL std::vector<qsf::vrectangle>::iterator end();
		QPLDLL std::vector<qsf::vrectangle>::const_iterator end() const;
		QPLDLL std::vector<qsf::vrectangle>::const_iterator cend() const;

		QPLDLL void add_rectangle(vrectangle rectangle);
		QPLDLL void add_rectangle(qsf::vector2f position, qsf::vector2f dimension);
		QPLDLL void add_rectangle(qsf::vector2f position, qsf::vector2f dimension, qsf::rgb color);

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QPLDLL qsf::vrectangles& operator=(const qsf::vrectangles& rectangles);

		std::vector<qsf::vrectangle> rectangles;
	};

	struct rectangles {

		QPLDLL qpl::size size() const;
		QPLDLL void resize(qpl::size new_size);
		QPLDLL void reserve(qpl::size new_size);
		QPLDLL void clear();
		QPLDLL void add(const qsf::rectangle& rect);

		QPLDLL qsf::rectangle& operator[](qpl::u32 index);
		QPLDLL const qsf::rectangle& operator[](qpl::u32 index) const;

		QPLDLL qsf::rectangle& front();
		QPLDLL const qsf::rectangle& front() const;

		QPLDLL qsf::rectangle& back();
		QPLDLL const qsf::rectangle& back() const;

		QPLDLL std::vector<qsf::rectangle>::iterator begin();
		QPLDLL std::vector<qsf::rectangle>::const_iterator begin() const;
		QPLDLL std::vector<qsf::rectangle>::const_iterator cbegin() const;

		QPLDLL std::vector<qsf::rectangle>::iterator end();
		QPLDLL std::vector<qsf::rectangle>::const_iterator end() const;
		QPLDLL std::vector<qsf::rectangle>::const_iterator cend() const;

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QPLDLL qsf::rectangles& operator=(const qsf::vrectangles& rectangles);

		std::vector<qsf::rectangle> rectangles_;
	};

	struct vpoint {
		qsf::vector2f position;
		qsf::rgb color;

		vpoint() {

		}

		vpoint(qsf::vector2f position, qsf::rgb color) {
			this->position = position;
			this->color = color;
		}

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QPLDLL vpoint& operator=(qsf::vector2f position);

		QPLDLL bool operator==(const vpoint& other) const;
		QPLDLL bool operator!=(const vpoint& other) const;
		//QPLDLL vpoint& with_color(qsf::rgb color);
	};
	struct point {
		qsf::vertex vertex;

		QPLDLL qsf::point& operator=(const qsf::vpoint& point);
		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
	};

	struct vpoints {
		vpoints(qpl::size size = qpl::size{}) {
			this->points.resize(size);
		}


		QPLDLL qpl::size size() const;
		QPLDLL void resize(qpl::size new_size);
		QPLDLL void reserve(qpl::size new_size);

		QPLDLL qsf::vpoint& operator[](qpl::u32 index);
		QPLDLL const qsf::vpoint& operator[](qpl::u32 index) const;

		QPLDLL qsf::vpoint& front();
		QPLDLL const qsf::vpoint& front() const;

		QPLDLL qsf::vpoint& back();
		QPLDLL const qsf::vpoint& back() const;


		QPLDLL std::vector<qsf::vpoint>::iterator begin();
		QPLDLL std::vector<qsf::vpoint>::const_iterator begin() const;
		QPLDLL std::vector<qsf::vpoint>::const_iterator cbegin() const;

		QPLDLL std::vector<qsf::vpoint>::iterator end();
		QPLDLL std::vector<qsf::vpoint>::const_iterator end() const;
		QPLDLL std::vector<qsf::vpoint>::const_iterator cend() const;


		QPLDLL void add_point(qsf::vpoint point);
		QPLDLL void add_point(qsf::vector2f position, qsf::rgb color);
		QPLDLL qsf::vlines as_lines() const;

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QPLDLL void clear();

		std::vector<qsf::vpoint> points;
	};

	struct points {
		points() {
			this->vertices.set_primitive_type(qsf::primitive_type::points);
		}
		points(qpl::size size) {
			this->vertices.resize(size);
		}


		QPLDLL void resize(qpl::size new_size);
		QPLDLL void reserve(qpl::size new_size);

		QPLDLL qsf::vertex& operator[](qpl::u32 index);
		QPLDLL const qsf::vertex& operator[](qpl::u32 index) const;

		QPLDLL qsf::vertex& front();
		QPLDLL const qsf::vertex& front() const;

		QPLDLL qsf::vertex& back();
		QPLDLL const qsf::vertex& back() const;


		QPLDLL qsf::vlines as_lines() const;
		QPLDLL qsf::points& operator=(const qsf::vpoints& points);
		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QPLDLL void clear();
		QPLDLL qpl::size size() const;
		qsf::vertex_array vertices;
	};



	struct vcircle {
		vcircle() {
			this->radius = 0.0f;
		}
		vcircle(qsf::vpoint point, qpl::f32 radius) {
			this->point = point;
			this->radius = radius;
			this->point.position.move(qsf::vector2f{ -this->radius, -this->radius });
		}
		vcircle(qsf::vector2f center, qpl::f32 radius, qsf::rgb color) {
			this->point.position = center - qsf::vector2f{ radius, radius };
			this->point.color = color;
			this->radius = radius;
		}

		QPLDLL void set_position(qsf::vector2f center);
		QPLDLL void set_radius(qpl::f32 radius);
		QPLDLL void set_color(qsf::rgb color);
		QPLDLL void set_center(qsf::vector2f center);
		QPLDLL void centerize();
		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		qsf::vpoint point;
		qpl::f32 radius;
	};
	struct circle {
		circle() {

		}
		circle(const qsf::vcircle& circle) {
			*this = circle;
		}
		circle(const qsf::circle& circle) {
			*this = circle;
		}

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QPLDLL qsf::circle& operator=(const qsf::vcircle& circle);
		QPLDLL qsf::circle& operator=(const qsf::circle& circle);

		sf::CircleShape circle_shape;
	};

	struct vcircles {
		QPLDLL void resize(qpl::size new_size);
		QPLDLL void reserve(qpl::size new_size);

		QPLDLL qsf::vcircle& operator[](qpl::u32 index);
		QPLDLL const qsf::vcircle& operator[](qpl::u32 index) const;

		QPLDLL qsf::vcircle& front();
		QPLDLL const qsf::vcircle& front() const;

		QPLDLL qsf::vcircle& back();
		QPLDLL const qsf::vcircle& back() const;

		QPLDLL void add_circle(qsf::vpoint point, qpl::f32 radius, qsf::rgb color);
		QPLDLL void add_circle(qsf::vector2f position, qpl::f32 radius, qsf::rgb color);

		QPLDLL qpl::size size() const;
		QPLDLL void clear();

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		std::vector<qsf::vcircle> circles;
	};

	struct circles {
		circles() {

		}
		circles(const qsf::vcircles& circles) {
			*this = circles;
		}
		circles(const qsf::circles& circles) {
			*this = circles;
		}

		QPLDLL void resize(qpl::size new_size);
		QPLDLL void reserve(qpl::size new_size);

		QPLDLL qsf::circle& operator[](qpl::u32 index);
		QPLDLL const qsf::circle& operator[](qpl::u32 index) const;

		QPLDLL qsf::circle& front();
		QPLDLL const qsf::circle& front() const;

		QPLDLL qsf::circle& back();
		QPLDLL const qsf::circle& back() const;

		QPLDLL void add_circle(const qsf::vcircle& circle);
		QPLDLL void add_circle(qsf::vpoint point, qpl::f32 radius, qsf::rgb color);
		QPLDLL void add_circle(qsf::vector2f position, qpl::f32 radius, qsf::rgb color);
		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QPLDLL qsf::circles& operator=(const qsf::vcircles& circles);
		QPLDLL qsf::circles& operator=(const qsf::circles& circles);

		QPLDLL qpl::size size() const;
		QPLDLL void clear();

		std::vector<qsf::circle> circles_;
	};

	struct vline {


		QPLDLL void set_a(qsf::vpoint point);
		QPLDLL void set_a(qsf::vector2f position);
		QPLDLL void set_b(qsf::vpoint point);
		QPLDLL void set_b(qsf::vector2f position);
		QPLDLL void set_color(qsf::rgb color);
		QPLDLL void set_a_color(qsf::rgb color);
		QPLDLL void set_b_color(qsf::rgb color);

		QPLDLL qsf::vector2f normal() const;
		QPLDLL qpl::f32 length() const;
		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		//pi radians (0 - 2 pi)
		QPLDLL qpl::f32 rotation() const;
		QPLDLL qsf::vline& rotate_around_a(qpl::f64 degree);
		QPLDLL qsf::vline& rotate_around_b(qpl::f64 degree);

		vpoint a;
		vpoint b;
	};

	struct line {
		QPLDLL void set_a(qsf::vpoint point);
		QPLDLL void set_a(qsf::vector2f position);
		QPLDLL void set_b(qsf::vpoint point);
		QPLDLL void set_b(qsf::vector2f position);
		QPLDLL void set_color(qsf::rgb color);
		QPLDLL void set_a_color(qsf::rgb color);
		QPLDLL void set_b_color(qsf::rgb color);

		QPLDLL qsf::vector2f normal() const;
		QPLDLL qpl::f32 length() const;
		QPLDLL qpl::f32 rotation() const;
		qsf::vline& rotate_a(qpl::f64 degree);
		qsf::vline& rotate_b(qpl::f64 degree);

		QPLDLL qsf::line& operator=(const qsf::vline& line);
		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		std::array<sf::Vertex, 2> vertices;
	};

	struct vlines {

		QPLDLL void resize(qpl::size new_size);
		QPLDLL void reserve(qpl::size new_size);

		QPLDLL qsf::vpoint& operator[](qpl::u32 index);
		QPLDLL const qsf::vpoint& operator[](qpl::u32 index) const;

		QPLDLL qsf::vpoint& front();
		QPLDLL const qsf::vpoint& front() const;

		QPLDLL qsf::vpoint& back();
		QPLDLL const qsf::vpoint& back() const;


		QPLDLL void clear();
		QPLDLL qpl::size size() const;
		QPLDLL void add_point(qsf::vpoint point);
		QPLDLL void add_point(qsf::vector2f position, qsf::rgb color = qsf::rgb::white);
		QPLDLL void complete();

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		std::vector<qsf::vpoint> points;
	};

	struct lines {
		lines() {
			this->vertices.set_primitive_type(qsf::primitive_type::line_strip);
		}
		lines(const qsf::vlines& lines) {
			this->vertices.set_primitive_type(qsf::primitive_type::line_strip);
			*this = lines;
		}

		QPLDLL void resize(qpl::size new_size);
		QPLDLL void reserve(qpl::size new_size);

		QPLDLL qsf::vertex& operator[](qpl::u32 index);
		QPLDLL const qsf::vertex& operator[](qpl::u32 index) const;

		QPLDLL qsf::vertex& front();
		QPLDLL const qsf::vertex& front() const;

		QPLDLL qsf::vertex& back();
		QPLDLL const qsf::vertex& back() const;


		QPLDLL void complete();

		QPLDLL qsf::lines& operator=(const qsf::vlines& lines);
		QPLDLL void clear();
		QPLDLL qpl::size size() const;
		QPLDLL void add_point(qsf::vpoint point);
		QPLDLL void add_point(qsf::vector2f position, qsf::rgb color = qsf::rgb::white);
		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		qsf::vertex_array vertices;
	};

	struct vthick_line {

		QPLDLL void set_a(qsf::vpoint point);
		QPLDLL void set_a(qsf::vector2f position);
		QPLDLL void set_b(qsf::vpoint point);
		QPLDLL void set_b(qsf::vector2f position);
		QPLDLL void set_color(qsf::rgb color);
		QPLDLL void set_a_color(qsf::rgb color);
		QPLDLL void set_b_color(qsf::rgb color);

		QPLDLL qsf::vpoints as_points() const;

		QPLDLL qsf::vector2f normal() const;
		QPLDLL qpl::f32 length() const;
		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		qsf::vpoint a;
		qsf::vpoint b;
		qpl::f32 thickness = 1.0f;
	};

	struct thick_line {
		thick_line() {

		}
		thick_line(const qsf::vthick_line& line) {
			*this = line;
		}

		QPLDLL void set_a(qsf::vpoint point);
		QPLDLL void set_a(qsf::vector2f position);
		QPLDLL void set_b(qsf::vpoint point);
		QPLDLL void set_b(qsf::vector2f position);
		QPLDLL void set_color(qsf::rgb color);
		QPLDLL void set_a_color(qsf::rgb color);
		QPLDLL void set_b_color(qsf::rgb color);
		QPLDLL void set_thickness(qpl::f32 thickness);

		QPLDLL qsf::vpoints as_points() const;
		QPLDLL qsf::vector2f normal() const;
		QPLDLL qpl::f32 length() const;
		QPLDLL qsf::thick_line& operator=(const qsf::vthick_line& line);
		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		std::array<sf::Vertex, 4> vertices;
	};
	struct vthick_lines {

		QPLDLL void resize(qpl::size new_size);
		QPLDLL void reserve(qpl::size new_size);

		QPLDLL qsf::vpoint& operator[](qpl::u32 index);
		QPLDLL const qsf::vpoint& operator[](qpl::u32 index) const;

		QPLDLL qsf::vpoint& front();
		QPLDLL const qsf::vpoint& front() const;

		QPLDLL qsf::vpoint& back();
		QPLDLL const qsf::vpoint& back() const;


		QPLDLL void add_thick_line(qsf::vpoint point);
		QPLDLL void add_thick_line(qsf::vector2f position, qsf::rgb color);
		QPLDLL void set_thickness(qpl::f32 thickness);
		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QPLDLL void clear();
		QPLDLL qpl::size size() const;

		qsf::vpoints points;
		qpl::f32 thickness = 1.0f;
	};
	struct thick_lines {
		thick_lines() {
			this->vertices.set_primitive_type(qsf::primitive_type::quads);
		}

		QPLDLL void resize(qpl::size new_size);
		QPLDLL void reserve(qpl::size new_size);

		QPLDLL qsf::vertex& operator[](qpl::u32 index);
		QPLDLL const qsf::vertex& operator[](qpl::u32 index) const;

		QPLDLL qsf::vertex& front();
		QPLDLL const qsf::vertex& front() const;

		QPLDLL qsf::vertex& back();
		QPLDLL const qsf::vertex& back() const;


		QPLDLL void add_thick_line(qsf::vpoint point, qpl::f32 thickness);
		QPLDLL void add_thick_line(qsf::vector2f position, qsf::rgb color, qpl::f32 thickness);
		QPLDLL qsf::thick_lines& operator=(const qsf::vthick_lines& lines);
		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QPLDLL void clear();
		QPLDLL qpl::size size() const;

		qsf::vertex_array vertices;
	};

	struct pixel_image {
		pixel_image() {
			this->vertices.set_primitive_type(qsf::primitive_type::quads);
		}

		QPLDLL void set_array_dimension(qsf::vector2u dimension);
		QPLDLL void set_pixel_dimension(qsf::vector2f dimension);
		QPLDLL void set_position(qsf::vector2f position);
		QPLDLL void create_positions();

		QPLDLL void set(qpl::size x, qpl::size y, qsf::rgb color);
		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;


		qsf::vector2u array_dimension;
		qsf::vector2f pixel_dimension;
		qsf::vector2f position;
		qsf::vertex_array vertices;
		bool positions_set = false;
	};

	struct vgraph {
		
		vgraph() {
			this->x_axis_string_function = [](qpl::size index) {
				return qpl::to_string(index);
			};
		}

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;


		struct data_point_info {

			qpl::f64 data = 0.0;
			qpl::f64 thickness = qpl::f64_min;
			qsf::frgb color = qsf::rgb::unset;

			qsf::vcircle circle;
			qsf::vtext text;

			data_point_info() {
				this->thickness = qpl::f64_min;
				this->color = qsf::frgb::unset;
			}
			data_point_info(qpl::f64 value) {
				this->data = value;
			}
			data_point_info(const data_point_info& other) {
				*this = other;
			}
			QPLDLL data_point_info& operator=(const data_point_info& other);

			QPLDLL data_point_info operator*(qpl::f64 n) const;
			QPLDLL data_point_info operator*(data_point_info other) const;
			QPLDLL data_point_info operator-(data_point_info other) const;
			QPLDLL data_point_info operator+(data_point_info other) const;
			QPLDLL bool operator<(data_point_info other) const;
			QPLDLL bool operator>(data_point_info other) const;
		};

		struct data_point {
			qpl::f64 data = 0.0;
			qpl::f64 thickness = qpl::f64_min;
			qsf::frgb color = qsf::rgb::unset;

			data_point() {

			}
			data_point(qpl::f64 data) : data(data) {

			}
			data_point(const data_point& other) {
				*this = other;
			}
			QPLDLL data_point& operator=(const data_point& other);

			QPLDLL data_point operator*(qpl::f64 n) const;
			QPLDLL data_point operator*(data_point other) const;
			QPLDLL data_point operator-(data_point other) const;
			QPLDLL data_point operator+(data_point other) const;
			QPLDLL bool operator<(data_point other) const;
			QPLDLL bool operator>(data_point other) const;
		};

		struct data_point_simple {
			qpl::f64 data = 0.0;

			data_point_simple() {

			}
			data_point_simple(qpl::f64 data) : data(data) {

			}
			data_point_simple(const data_point_simple& other) {
				*this = other;
			}
			QPLDLL data_point_simple& operator=(const data_point_simple& other);

			QPLDLL data_point_simple operator*(qpl::f64 n) const;
			QPLDLL data_point_simple operator*(data_point_simple other) const;
			QPLDLL data_point_simple operator-(data_point_simple other) const;
			QPLDLL data_point_simple operator+(data_point_simple other) const;
			QPLDLL bool operator<(data_point_simple other) const;
			QPLDLL bool operator>(data_point_simple other) const;
		};

		qpl::f64 min_value = qpl::f64_min;
		qpl::f64 max_value = qpl::f64_max;

		qpl::f64 height_delta = 0.1;

		qsf::rgb x_axis_color = qsf::rgb::unset;
		qsf::rgb y_axis_color = qsf::rgb::unset;
		qsf::rgb axis_color = qsf::rgb::white;
		qpl::f64 y_axis_text_space = 40.0;
		qpl::size y_axis_line_count = 10u;
		qsf::vtext y_axis_text;
		bool y_axis_text_left = true;
		bool y_axis_text_percent = false;
		qpl::size y_axis_text_precision = 5u;
		bool use_y_axis = false;

		qpl::f64 x_axis_text_space = 5.0;
		qpl::size x_axis_line_frequency = 200u;
		qsf::vtext x_axis_text;
		bool x_axis_text_left = true;
		bool x_axis_text_percent = false;
		qpl::size x_axis_text_precision = 5u;


		qpl::size x_data_steps = 10u;
		qpl::u32 desired_x_axis_lines = 10u;
		qpl::u32 desired_visible_size = 200u;

		qpl::size display_last_n_entries = qpl::size_max;
		qpl::size index_start = 0u;
		qpl::size index_end = qpl::size_max;
		qpl::size index_skip_size = 1u;

		bool use_x_axis = false;
		std::function<std::string(qpl::size)> x_axis_string_function;

		qsf::rgb axis_line_color = qsf::rgb(30, 30, 30);
		qpl::f64 axis_thickness = 1.5f;

		std::string font;
		qpl::f64 zoom_factor = 1.3;
		qsf::vector2f position;
		qsf::vector2f dimension = { 500, 300 };


		enum class interpolation_type : qpl::u32 {
			unset = 0,
			linear = 1,
			cubic = 2,
		};

		qsf::rgb color = qsf::rgb::white;
		qpl::f64 thickness = 1.0f;
		interpolation_type interpolation = interpolation_type::cubic;
		qpl::size interpolation_steps = 1u;


		struct info_graph {
			template<typename T>
			void set_data(const std::vector<T>& data) {
				this->data.resize(data.size());
				for (qpl::u32 i = 0u; i < data.size(); ++i) {
					this->data[i].data = static_cast<qpl::f64>(data[i]);
					this->data[i].color = this->color;
					this->data[i].thickness = this->thickness;
				}
			}
			template<typename T>
			void set_data(const std::vector<T>& data, qsf::rgb color, qpl::f64 thickness) {
				this->color = color;
				this->thickness = thickness;
				this->set_data(data);
			}
			QPLDLL void add_data(qpl::f64 data);
			QPLDLL void add_data(qpl::f64 data, qsf::rgb color);
			QPLDLL void add_data(qpl::f64 data, qsf::rgb color, qpl::f64 thickness);


			QPLDLL qpl::f64 get_percentage_height_at(qpl::size index) const;
			QPLDLL std::pair<data_point_info, data_point_info> get_low_high() const;
			QPLDLL qpl::size size() const;
			QPLDLL data_point_info& operator[](qpl::size index);
			QPLDLL const data_point_info& operator[](qpl::size index) const;

			QPLDLL std::vector<data_point_info>::iterator begin();
			QPLDLL std::vector<data_point_info>::const_iterator begin() const;
			QPLDLL std::vector<data_point_info>::const_iterator cbegin();

			QPLDLL std::vector<data_point_info>::iterator end();
			QPLDLL std::vector<data_point_info>::const_iterator end() const;
			QPLDLL std::vector<data_point_info>::const_iterator cend();

			interpolation_type interpolation = interpolation_type::cubic;
			qsf::rgb color = qsf::rgb::unset;
			qpl::f64 thickness = qpl::f64_min;
			qpl::size interpolation_steps = qpl::size_max;


			std::vector<data_point_info> data;
		};

		struct standard_graph {
			template<typename T>
			void set_data(const std::vector<T>& data) {
				this->data.resize(data.size());
				for (qpl::u32 i = 0u; i < data.size(); ++i) {
					this->data[i].data = static_cast<qpl::f64>(data[i]);
					this->data[i].color = this->color;
					this->data[i].thickness = this->thickness;
				}
			}
			template<typename T>
			void set_data(const std::vector<T>& data, qsf::rgb color, qpl::f64 thickness) {
				this->color = color;
				this->thickness = thickness;
				this->set_data(data);
			}
			QPLDLL void add_data(qpl::f64 data);
			QPLDLL void add_data(qpl::f64 data, qsf::rgb color);
			QPLDLL void add_data(qpl::f64 data, qsf::rgb color, qpl::f64 thickness);

			QPLDLL qpl::f64 get_percentage_height_at(qpl::size index) const;
			QPLDLL std::pair<data_point, data_point> get_low_high() const;
			QPLDLL qpl::size size() const;
			QPLDLL data_point& operator[](qpl::size index);
			QPLDLL const data_point& operator[](qpl::size index) const;

			QPLDLL std::vector<data_point>::iterator begin();
			QPLDLL std::vector<data_point>::const_iterator begin() const;
			QPLDLL std::vector<data_point>::const_iterator cbegin();

			QPLDLL std::vector<data_point>::iterator end();
			QPLDLL std::vector<data_point>::const_iterator end() const;
			QPLDLL std::vector<data_point>::const_iterator cend();

			interpolation_type interpolation = interpolation_type::cubic;
			qsf::rgb color = qsf::rgb::unset;
			qpl::f64 thickness = qpl::f64_min;
			qpl::size interpolation_steps = qpl::size_max;


			std::vector<data_point> data;
		};

		struct simple_graph {
			template<typename T>
			void set_data(const std::vector<T>& data) {
				this->data.resize(data.size());
				for (qpl::u32 i = 0u; i < data.size(); ++i) {
					this->data[i].data = static_cast<qpl::f64>(data[i]);
				}
			}
			template<typename T>
			void set_data(const std::vector<T>& data, qsf::rgb color, qpl::f64 thickness) {
				this->color = color;
				this->thickness = thickness;
				this->set_data(data);
			}
			QPLDLL void add_data(qpl::f64 data);

			QPLDLL qpl::f64 get_percentage_height_at(qpl::size index) const;
			QPLDLL std::pair<data_point_simple, data_point_simple> get_low_high() const;
			QPLDLL qpl::size size() const;
			QPLDLL data_point_simple& operator[](qpl::size index);
			QPLDLL const data_point_simple& operator[](qpl::size index) const;

			QPLDLL std::vector<data_point_simple>::iterator begin();
			QPLDLL std::vector<data_point_simple>::const_iterator begin() const;
			QPLDLL std::vector<data_point_simple>::const_iterator cbegin();

			QPLDLL std::vector<data_point_simple>::iterator end();
			QPLDLL std::vector<data_point_simple>::const_iterator end() const;
			QPLDLL std::vector<data_point_simple>::const_iterator cend();

			interpolation_type interpolation = interpolation_type::cubic;
			qsf::rgb color = qsf::rgb::unset;
			qpl::f64 thickness = qpl::f64_min;
			qpl::size interpolation_steps = qpl::size_max;


			std::vector<data_point_simple> data;
		};

		bool drag = false;
		qsf::vector2f click_position;


		QPLDLL void check_x_axis();
		QPLDLL void enable_track_new_entries();
		QPLDLL void disable_track_new_entries();
		QPLDLL void enable_axis_info();
		QPLDLL void update(const event_info& event_info);

		QPLDLL void set_font(std::string name);
		QPLDLL std::string get_font() const;

		QPLDLL qpl::f64 true_graph_width() const;
		QPLDLL qpl::f64 true_graph_height() const;
		QPLDLL qsf::vector2f true_graph_dimension() const;

		QPLDLL std::pair<qpl::f64, qpl::f64> get_low_high() const;
		QPLDLL qpl::size total_graph_size() const;
		QPLDLL qpl::size graph_element_size() const;
		QPLDLL qpl::size visible_element_size() const;
		QPLDLL qpl::u32 visible_index_start() const;
		QPLDLL qpl::u32 visible_index_end() const;
		QPLDLL bool is_range_enabled() const;

		QPLDLL void add_info_graph(std::string name);
		QPLDLL info_graph& get_info_graph(std::string name);
		QPLDLL const info_graph& get_info_graph(std::string name) const;
		QPLDLL std::span<const data_point_info> get_info_graph_span(std::string name) const;

		QPLDLL void add_standard_graph(std::string name);
		QPLDLL standard_graph& get_standard_graph(std::string name);
		QPLDLL const standard_graph& get_standard_graph(std::string name) const;
		QPLDLL std::span<const data_point> get_standard_graph_span(std::string name) const;

		QPLDLL void add_simple_graph(std::string name);
		QPLDLL simple_graph& get_simple_graph(std::string name);
		QPLDLL const simple_graph& get_simple_graph(std::string name) const;
		QPLDLL std::span<const data_point_simple> get_simple_graph_span(std::string name) const;


		std::unordered_map<std::string, info_graph> info_graphs;
		std::unordered_map<std::string, standard_graph> standard_graphs;
		std::unordered_map<std::string, simple_graph> simple_graphs;

		qsf::rgb background_color = qsf::rgb::transparent;
	};

	struct graph {

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QPLDLL qsf::graph& operator=(const qsf::vgraph& graph);


		std::vector<std::vector<qsf::text>> circle_texts;
		std::vector<qsf::circles> circles;
		std::vector<qsf::thick_lines> y_lines;
		std::vector<qsf::text> y_texts;
		std::vector<qsf::thick_lines> x_lines;
		std::vector<qsf::text> x_texts;

		std::vector<qsf::thick_lines> lines;

		qsf::rectangle background;
	};

	struct vbutton {

		QPLDLL void set_dimension(qsf::vector2f dimension);
		QPLDLL void set_position(qsf::vector2f position);
		QPLDLL void set_center(qsf::vector2f center);
		QPLDLL void set_background_color(qsf::rgb color);
		QPLDLL void set_hover_background_color(qsf::rgb color);
		QPLDLL void set_text_color(qsf::rgb color);
		QPLDLL void set_text_font(std::string font);
		QPLDLL void set_text_character_size(qpl::u32 character_size);
		QPLDLL void set_text_style(qpl::u32 character_style);
		QPLDLL void set_text(std::string text);
		QPLDLL void centerize_text();
		QPLDLL bool is_hovering() const;
		QPLDLL bool is_clicked() const;
		QPLDLL void update(const event_info& event_info);

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QPLDLL qsf::vbutton& operator=(const qsf::vbutton& button);

		bool outline_on_hover = true;
		bool invert_on_hover = true;
		qsf::rgb text_color;
		qsf::rgb hover_background_color;
		qsf::rgb background_color;
		qsf::vtext text;
		qsf::vrectangle background;
		bool hovering;
		bool clicked;
	};

	struct button {

		QPLDLL void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QPLDLL qsf::button& operator=(const qsf::vbutton& button);



		QPLDLL void set_dimension(qsf::vector2f dimension);
		QPLDLL void set_position(qsf::vector2f position);
		QPLDLL void set_center(qsf::vector2f center);
		QPLDLL void set_background_color(qsf::rgb color);
		QPLDLL void set_hover_background_color(qsf::rgb color);
		QPLDLL void set_text_color(qsf::rgb color);
		QPLDLL void set_text_font(std::string font);
		QPLDLL void set_text_character_size(qpl::u32 character_size);
		QPLDLL void set_text_style(qpl::u32 character_style);
		QPLDLL void set_text(std::string text);
		QPLDLL void centerize_text();
		QPLDLL bool is_hovering() const;
		QPLDLL bool is_clicked() const;
		QPLDLL void update(const event_info& event_info);

		bool outline_on_hover = true;
		bool invert_on_hover = true;
		qsf::rgb text_color = qsf::rgb::white;
		qsf::rgb hover_background_color = qsf::rgb::white;
		qsf::rgb background_color = qsf::rgb::black;
		qsf::text text;
		qsf::rectangle background;
		bool hovering;
		bool clicked;
	};

	namespace detail {
		QPLDLL extern std::unordered_map<std::string, qsf::text> texts;
	}

	QPLDLL qsf::text& get_text(const std::string& name = "QSF_DEFAULT");
	QPLDLL void add_text(const std::string& name = "QSF_DEFAULT");

}

#endif
#endif
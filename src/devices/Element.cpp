/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file      Element.cpp
 * @since     Jun 22, 2018
 * @author    Patricio A. Rossi (MeduZa)
 *
 * @copyright Copyright © 2018 - 2025 Patricio A. Rossi (MeduZa)
 *
 * @copyright LEDSpicer is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * @copyright LEDSpicer is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * @copyright You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Element.hpp"

using namespace LEDSpicer::Devices;

void Element::setColor(const Color& color) {
	const Color& newColor(brightness ? color.fade(brightness) : color);
	// Multiple RGB.
	if (leds.size() > 3) {
		for (size_t i = 0; i < leds.size(); i += 3) {
			*leds[i + Color::Channels::Red]   = newColor.getR();
			*leds[i + Color::Channels::Green] = newColor.getG();
			*leds[i + Color::Channels::Blue]  = newColor.getB();
		}
	}
	// Single RGB.
	if (leds.size() == 3) {
		*leds[Color::Channels::Red]   = newColor.getR();
		*leds[Color::Channels::Green] = newColor.getG();
		*leds[Color::Channels::Blue]  = newColor.getB();
	}
	// Handle solenoids.
	else if (timeOn) {
		// set solenoid off
		if (newColor == Color::Off) {
			*leds[SINGLE_LED] = 0;
		}
		// On, always kick full intense.
		else if (not *leds[SINGLE_LED]) {
			*leds[SINGLE_LED] = 255;
			clockTime = std::chrono::system_clock::now() + std::chrono::milliseconds(timeOn);
		}
	}
	// Single led in monochrome.
	else {
		*leds[SINGLE_LED] = newColor.getMonochrome();
	}
}

void Element::setColor(const Color& color, const Color::Filters& filter, uint8_t percent) {
	if (filter == Color::Filters::Normal)
		setColor(color);
	else
		setColor(*getColor().set(color, filter, percent));
}

LEDSpicer::Color Element::getColor() const {
	Color color;
	if (leds.size() == 1)
		color.set(*leds[SINGLE_LED], *leds[SINGLE_LED], *leds[SINGLE_LED]);
	else
		color.set(
			*leds[Color::Channels::Red],
			*leds[Color::Channels::Green],
			*leds[Color::Channels::Blue]
		);
	return color;
}

void Element::setLedValue(uint16_t led, uint8_t val) {
	*leds[led] = val;
}

uint8_t Element::getLedValue(uint16_t led) const {
	return *leds[led];
}

uint8_t* const Element::getLed(uint16_t led) const {
	if (led > leds.size())
		throw Error("Invalid led number");
	return leds[led];
}

const vector<uint8_t*>& Element::getLeds() const {
	return leds;
}

uint8_t Element::size() const {
	return leds.size();
}

const string Element::getName() const {
	return name;
}

const LEDSpicer::Color& Element::getDefaultColor() const {
	return defaultColor;
}

bool Element::isTimed() const {
	return timeOn != 0;
}

void Element::checkTime() {
	if (*leds[SINGLE_LED] and std::chrono::system_clock::now() > clockTime)
		*leds[SINGLE_LED] = 0;
}

void Element::draw() {
	cout <<
		std::left << std::setfill(' ') << std::setw(20) << name <<
		" Led: " << (leds.size() == 1 ? (timeOn ? "Solenoid" : "Single Color") : (leds.size() == 3 ? "RGB" : "Multi RGB"));

	if (timeOn)
		cout << std::left << std::setw(6) << (to_string(timeOn) + "ms");

	cout <<
		" Default Color: " << std::left << std::setw(15) << defaultColor.getName() <<
		(brightness ? " Brightness:" + to_string(brightness) + "%" : "") << endl;

	if (timeOn)
		cout << "  * Connected timed hardware like a solenoids" << endl;
}

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file      Ultimate.hpp
 * @since     Jun 23, 2018
 * @author    Patricio A. Rossi (MeduZa)
 * @copyright Copyright © 2018 - 2019 Patricio A. Rossi (MeduZa)
 */

// For special io format
#include <iomanip>

#include "Ultimarc.hpp"

#ifndef ULTIMATE_HPP_
#define ULTIMATE_HPP_ 1

#define IPAC_ULTIMATE_NAME       "Ultimarc Ipac Ultimate IO"
#define IPAC_ULTIMATE_PRODUCT    0x0410
#define IPAC_ULTIMATE_WVALUE     0x0203
#define IPAC_ULTIMATE_INTERFACE  2
#define IPAC_ULTIMATE_LEDS       96
#define IPAC_ULTIMAGE_MAX_BOARDS 4

#define ULTIMAGE_MSG(byte1, byte2) {0x03, 0, 0, byte1, byte2}

namespace LEDSpicer {
namespace Devices {
namespace Ultimarc {

/**
 * LEDSpicer::Devices::Ultimate
 * Class to keep Ultimate I/O data and functionality.
 */
class Ultimate : public Ultimarc {

public:

	/**
	 * @param boardId
	 */
	Ultimate(uint8_t boardId, umap<string, string>& options) :
	Ultimarc(
		IPAC_ULTIMATE_WVALUE,
		0, // to be defined.
		IPAC_ULTIMATE_LEDS,
		IPAC_ULTIMAGE_MAX_BOARDS,
		boardId,
		IPAC_ULTIMATE_NAME
	) {}

	virtual ~Ultimate() = default;

	virtual void drawHardwarePinMap();

	void transfer();

	uint16_t getProduct();

	virtual void resetLeds();

protected:

	virtual void afterConnect();

};

}}} /* namespace LEDSpicer */

deviceFactory(LEDSpicer::Devices::Ultimarc::Ultimate)

#endif /* ULTIMATE_HPP_ */

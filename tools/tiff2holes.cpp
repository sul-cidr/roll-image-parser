//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sun Nov 26 08:10:23 PST 2017
// Last Modified: Thu Mar  5 09:56:35 PST 2020
// Filename:      tiff2holes.cpp
// Web Address:
// Syntax:        C++
// vim:           ts=3:nowrap:ft=text
//
// Description:   Identify holes in TIFF images of piano rolls.  The same
//                program as markholes.cpp, but this one does not do analytic
//                markup of the copy of the input image.
// Options:
//     -r         Assume a Red Welte-Mignon piano roll (T-100).
//     -g         Assume a Green Welte-Mignon piano roll (T-98).
//     -l         Assume a Welte-Mignon (De Luxe) Licensee piano roll
//     -a         Assume an Ampico [A] (older) piano roll, but option not yet active.
//     -b         Assume an Ampico B (newer) piano roll, but option not yet active.
//     -d         Assume a Duo-Art piano roll, but option not yet active.
//     --65       Assume a 65-note Duo-art universal piano roll
//     --88       Assume a 88-note roll
//     -t         Set the paper/hole brightness boundary (from 0-255, with 249 being the default).
//

#include "RollImage.h"
#include "Options.h"

#include <vector>

using namespace std;
using namespace rip;

///////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	Options options;
	options.define("r|red|red-welte|welte-red=b", "Assume Red-Welte (T-100) piano roll");
	options.define("g|green|green-welte|welte-green=b", "Assume Green-Welte (T-98) piano roll");
	options.define("l|licensee|licensee-welte|welte-licensee=b", "Assume Licensee piano roll");
	options.define("a|ampico=b", "Assume Ampico [A] piano roll (EXPERIMENTAL)");
	options.define("b|ampico-b=b", "Assume Ampico B piano roll (EXPERIMENTAL)");
	options.define("d|duo-art=b", "Assume Aeolean Duo-Art piano roll (EXPERIMENTAL)");
	options.define("5|65|65-note|65-hole=b", "Assume 65-note roll");
	options.define("8|88|88-note|88-hole=b", "Assume 88-note roll");
	options.define("t|threshold=i:249", "Brightness threshold for hole/paper separation");
	options.define("m|monochrome=b", "Input image is a monochrome (single-channel) TIFF");
	options.define("s|disregard-rewind-hole=b", "Skip rewind hole correction for tracker->MIDI mapping");
	options.define("n|no-leaders=b", "Roll image has no tapered leader/preleader sections before holes");
	options.define("e|emulate-roll-acceleration=b", "Add tempo events to note MIDI for acceleration");
	options.define("i|alignment-shift=i:0", "Shift leftmost valid position for tracker->MIDI mapping");
	options.process(argc, argv);

	if (options.getArgCount() != 1) {
		cerr << "Usage: tiff2holes [-rgl58tmse] file.tiff > analysis.txt" << endl;
		cerr << "file.tiff must be a 24-bit color image, uncompressed" << endl;
		cerr << "unless -m is supplied; then file.tiff must be a monochrome" << endl;
		cerr << "(8-bit, single-channel) image, uncompressed" << endl;
		exit(1);
	}

	RollImage roll;
	if (!roll.open(options.getArg(1))) {
		cerr << "Input filename " << options.getArg(1) << " cannot be opened" << endl;
		exit(1);
	}

	if (options.getBoolean("red-welte")) {
		roll.setRollTypeRedWelte();
	} else if (options.getBoolean("green-welte")) {
		roll.setRollTypeGreenWelte();
	} else if (options.getBoolean("licensee-welte")) {
		roll.setRollTypeLicenseeWelte();
	} else if (options.getBoolean("65-note")) {
		roll.setRollType65Note();
	} else if (options.getBoolean("88-note")) {
		roll.setRollType88Note();
	} else if (options.getBoolean("ampico")) {
		roll.setRollTypeAmpico();
	} else if (options.getBoolean("ampico-b")) {
		roll.setRollTypeAmpicoB();
	} else if (options.getBoolean("duo-art")) {
		roll.setRollTypeDuoArt();
	} else {
		cerr << "A Roll type is required:" << endl;
		cerr << "   -r   == for red Welte rolls"   << endl;
		cerr << "   -g   == for green Welte rolls" << endl;
		cerr << "   -l   == for Licensee Welte rolls" << endl;
		cerr << "   --65 == for 65-note rolls"     << endl;
		cerr << "   --88 == for 88-note rolls"     << endl;
		cerr << "   -a   == for Ampico [A] rolls"  << endl;
		cerr << "   -b   == for Ampico B rolls"    << endl;
		cerr << "   -d   == for Duo-Art rolls"     << endl;
		exit(1);
	}

    if (options.getBoolean("disregard-rewind-hole")) {
		roll.setRewindCorrection(false);
	}

	if (options.getBoolean("emulate-roll-acceleration")) {
		roll.toggleAccelerationEmulation(true);
	}

	if (options.getBoolean("no-leaders")) {
		roll.setMissingLeaders(true);
	}

	int threshold = options.getInteger("threshold");

	int trackerShift = options.getInteger("alignment-shift");

	roll.setDebugOn();
	roll.setWarningOn();
	roll.setMonochrome(options.getBoolean("monochrome"));
	roll.loadGreenChannel(threshold);
	roll.setAlignmentShift(trackerShift);
	roll.analyze();
	roll.printRollImageProperties();

	return 0;
}


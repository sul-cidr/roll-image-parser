//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Thu Dec  7 21:46:42 PST 2017
// Last Modified: Mon Mar 25 22:38:36 PDT 2019
// Filename:      RollOptions.cpp
// Web Address:
// Syntax:        C++
// vim:           ts=3:nowrap:ft=text
//
// Description:   Options for parsing images of piano rolls.
//

#include "RollOptions.h"

using namespace std;

namespace rip  {


//////////////////////////////
//
// RollOptions::RollOptions --
//

RollOptions::RollOptions(void) {
	reset();
}



//////////////////////////////
//
// RollOptions::~RollOptions --
//

RollOptions::~RollOptions() {
	// do nothing
}



//////////////////////////////
//
// RollOptions::reset -- Set to default parameters.
//

void RollOptions::reset(void) {
	m_minTrackerSpacingToPaperEdge = 0.50;
	m_maxHoleWidth                 = 1.50; // wide for rewind hole of duoart salesman
	m_aspectRatioThreshold         = 1.25;
	m_pixelsPerInch                = 300;
	m_majorAxisThreshold           = 13.0;
	m_circularityThreshold         =  0.4;
	m_maxHoleCount                 = 100000;
	m_maxTearFill                  = 100000;
	m_attackLineSpacing            = 10;
	m_holeShiftCutoff              = 3.0;
};



//////////////////////////////
//
// RollOptions::getPixelsPerInch -- 
//

double RollOptions::getPixelsPerInch(void) {
	return m_pixelsPerInch;
}



//////////////////////////////
//
// RollOptions::getAspectRatioThreshold --
//

double RollOptions::getAspectRatioThreshold(void) {
	return m_aspectRatioThreshold;
}



//////////////////////////////
//
// RollOptions::getAspectRatioThreshold --
//

void RollOptions::setAspectRatioThreshold(double value) {
	m_aspectRatioThreshold = value;
}



//////////////////////////////
//
// RollOptions::getMaxHoleTrackerWidth --
//

double RollOptions::getMaxHoleTrackerWidth(void) {
	return m_maxHoleWidth;
}



//////////////////////////////
//
// RollOptions::setMaxHoleTrackerWidth --
//

void RollOptions::setMaxHoleTrackerWidth(double value) {
		m_maxHoleWidth = value;
}



//////////////////////////////
//
// RollOptions::getMinTrackerEdge --
//

double RollOptions::getMinTrackerEdge(void) {
	return m_minTrackerSpacingToPaperEdge;
}



//////////////////////////////
//
// RollOptions::setMinTrackerEdge --
//

void RollOptions::setMinTrackerEdge(double value) {
		m_minTrackerSpacingToPaperEdge = value;
}



//////////////////////////////
//
// RollOptions::getMinTrackerEdge --
//

double RollOptions::getMajorAxisCutoff(void) {
	return m_majorAxisThreshold;
}



//////////////////////////////
//
// RollOptions::setMinTrackerEdge --
//


void RollOptions::setMajorAxisCutoff(double value) {
	m_majorAxisThreshold = value;
}



//////////////////////////////
//
// RollOptions::getCircularityThreshold --
//

double RollOptions::getCircularityThreshold(void) {
	return m_circularityThreshold;
}



//////////////////////////////
//
// RollOptions::setCircularityThreshold --
//

void RollOptions::setCircularityThreshold(double value) {
	m_circularityThreshold = value;
}



//////////////////////////////
//
// RollOptions::getMaxHoleCount --
//

int RollOptions::getMaxHoleCount(void) {
	return m_maxHoleCount;
}



//////////////////////////////
//
// RollOptions::setMaxHoleCount --
//

void RollOptions::setMaxHoleCount(int value) {
	m_maxHoleCount = value;
}



//////////////////////////////
//
// RollOptions::getMaxTearFill --
//

int RollOptions::getMaxTearFill(void) {
	return m_maxTearFill;
}



//////////////////////////////
//
// RollOptions::setMaxTearFill --
//

void RollOptions::setMaxTearFill(int value) {
	m_maxTearFill = value;
}



//////////////////////////////
//
// RollOptions::getAttackLineSpacing --
//

int RollOptions::getAttackLineSpacing(void) {
	return m_attackLineSpacing;
}



//////////////////////////////
//
// RollOptions::setAttackLineSpacing --
//

void RollOptions::setAttackLineSpacing(int value) {
	m_attackLineSpacing = value;
}



//////////////////////////////
//
// RollOptions::getHoleShiftCutoff --
//

double RollOptions::getHoleShiftCutoff(void) {
	return m_holeShiftCutoff;
}



//////////////////////////////
//
// RollOptions::setHoleShiftCutoff --
//

void RollOptions::setHoleShiftCutoff(double value) {
	m_holeShiftCutoff = value;
}



//////////////////////////////
//
// RollOptions::getRollType -- Return the roll type being processed:
//   "" = unknown/unspecified
//   "welte-red"      = Welte Mignon T-100 red roll
//   "welte-green"    = Welte Mignon T-98 green roll
//   "welte-licensee" = Welte Mignon (De Luxe) Licensee
//   "ampico"         = AMPICO roll (variation not specified)
//   "ampico-a"       = AMPICO roll, earlier model
//   "ampico-b"       = AMPICO roll, later model
//   "duoart"         = Aeolean Duo-Art
//   "65-note"        = 64-note roll (6 holes/inch)
//   "88-note"        = 88-note roll standard (9 holes/inch)
//

std::string RollOptions::getRollType(void) {
	return m_rollType;
}



//////////////////////////////
//
// RollOptions::setRollTypeRedWelte -- Apply settings suitable for Red Welte (T-100) piano rolls.
//
// red Welte tracker holes:
//
//   10 expression on bass side:
//       1:  MF-Off                          MIDI Key 14
//       2:  MF-On                           MIDI Key 15
//       3:  Crescendo-Off                   MIDI Key 16
//       4:  Crescendo-On                    MIDI Key 17
//       5:  Forzando-Off                    MIDI Key 18
//       6:  Forzando-On                     MIDI Key 19
//       7:  Soft-Pedal-Off                  MIDI Key 20
//       8:  Soft-Pedal-On                   MIDI Key 21
//       9:  Motor-Off                       MIDI Key 22
//       10: Motor-On                        MIDI Key 23
//   Then 80 notes from C1 to G7 (MIDI notes 24 to 103)
//       11: C1                              MIDI Key 24
//       ...
//       53:  F#4                            MIDI Key 66
//    Treble register (note bass register has more notes):
//       54:  G4                             MIDI Key 67
//       ...
//       90:  G7                             MIDI Key 103
//   10 expression holes on the treble side:
//       91:  -10: Rewind                    MIDI Key 104
//       92:  -9:  Electric-Cutoff           MIDI Key 105
//       93:  -8:  Sustain-Pedal-On          MIDI Key 106
//       94:  -7:  Sustain-Pedal-Off         MIDI Key 107
//       95:  -6:  Forzando-On               MIDI Key 108
//       96:  -5:  Forzando-Off              MIDI Key 109
//       97:  -4:  Crescendo-On              MIDI Key 110
//       98:  -3:  Crescendo-Off             MIDI Key 111
//       99:  -2:  Mezzo-Forte-On            MIDI Key 112
//       100: -1:  Mezzo-Forte-Off           MIDI Key 113
//
//

void RollOptions::setRollTypeRedWelte(void) {
	m_rollType = "welte-red";
	m_minTrackerSpacingToPaperEdge = 1.6;
	m_rewindHole = 91;  // 91st hole from left (bass)
	m_rewindHoleMidi = 104;
	m_trackerHoles = 100;

	m_bass_midi = 14;   // first MIDI Note on bass side of paper
	m_treble_midi = 113; // first MIDI Note on treble side of paper

	m_bassExpressionTrackStartNumberLeft = 1;
	m_bassExpressionTrackStartMidi = 14;
	m_bassNotesTrackStartNumberLeft = 11;
	m_bassNotesTrackStartMidi = 24;
	m_trebleNotesTrackStartNumberLeft = 54;
	m_trebleNotesTrackStartMidi = 67;
	m_trebleExpressionTrackStartNumberLeft = 91;
	m_trebleExpressionTrackStartMidi = 104;

	hasExpressionMidiFileSetup();
}



//////////////////////////////
//
// RollOptions::setRollTypeGreenWelte -- Apply settings suitable for Green Welte (T-98) piano rolls.
//
// Peter Phillips dissertation: https://ses.library.usyd.edu.au/bitstream/2123/16939/1/Piano%20Rolls.pdf
//
// green Welte tracker holes:
//
//   5 expression holes on bass side:
//       1:  Bass Sforzando piano (& rewind) MIDI Key 16
//       2:  Bass Mezzoforte                 MIDI Key 17
//       3:  Sustain pedal                   MIDI Key 18
//       4:  Bass Crescendo                  MIDI Key 19
//       5:  Bass Sforzando forte            MIDI Key 20
//   Then 88 notes from A0 to C8 (MIDI notes 21 to 108)
//       6: A0                               MIDI Key 21
//       ...
//       51:  F#4                            MIDI Key 66
//    Treble register:
//       52:  G4                             MIDI Key 67
//       ...
//       93:  C8                             MIDI Key 108
//   5 expression holes on the treble side:
//       94:  -5:  Treble Sforzando forte    MIDI Key 109
//       95:  -4:  Treble Crescendo          MIDI Key 110
//       96:  -3:  Soft pedal                MIDI Key 111
//       97:  -2:  Treble Mezzoforte         MIDI Key 112
//       98:  -1:  Treble Sforzando piano    MIDI Key 113
//

void RollOptions::setRollTypeGreenWelte(void) {
	m_rollType = "welte-green";
	m_minTrackerSpacingToPaperEdge = 1.6; // check
	m_rewindHole = 1;  // 1st hole from left (bass), but only if "long"
	m_rewindHoleMidi = 16;
	m_trackerHoles = 98;

	m_bass_midi = 16;   // first MIDI Note on bass side of paper
	m_treble_midi = 113; // first MIDI Note on treble side of paper

	m_bassExpressionTrackStartNumberLeft = 1;
	m_bassExpressionTrackStartMidi = 16;
	m_bassNotesTrackStartNumberLeft = 6;
	m_bassNotesTrackStartMidi = 21;

	m_trebleNotesTrackStartNumberLeft = 52;
	m_trebleNotesTrackStartMidi = 67;

	m_trebleExpressionTrackStartNumberLeft = 94;
	m_trebleExpressionTrackStartMidi = 109;

	hasExpressionMidiFileSetup();
}



//////////////////////////////
//
// RollOptions::setRollTypeLicenseeWelte -- Apply settings suitable for Welte Licensee (US De Luxe) piano rolls.
//
// Welte Licensee tracker holes:
//
//   8 expression holes on bass side:
//       1:  Bass Mezzoforte off             MIDI Key 16
//       2:  Bass Mezzoforte on              MIDI Key 17
//       3:  Bass Crescendo off              MIDI Key 18
//       4:  Bass Crescendo on               MIDI Key 19
//       5:  Bass Sforzando off              MIDI Key 20
//       6:  Bass Sforzando on               MIDI Key 21
//       7:  Soft pedal off                  MIDI Key 22
//       8:  Soft pedal on                   MIDI Key 23
//   Then 80 notes from C1 to G7 (MIDI notes 24 to 103)
//       9:  C1                              MIDI Key 24
//       ...
//       51:  F#4                            MIDI Key 66
//    Treble register:
//       52:  G4                             MIDI Key 67
//       ...
//       88:  G7                             MIDI Key 103
//   10 expression holes on the treble side:
//       89: -10:  Rewind                    MIDI Key 104
//       90:  -9:  Blank                    [MIDI Key 105]
//       91:  -8:  Sustain pedal on          MIDI Key 106
//       92:  -7:  Sustain pedal off         MIDI Key 107
//       93:  -6:  Treble Sforzando on       MIDI Key 108
//       94:  -5:  Treble Sforzando off      MIDI Key 109
//       95:  -4:  Treble Crescendo on       MIDI Key 110
//       96:  -3:  Treble Crescendo off      MIDI Key 111
//       97:  -2:  Treble Mezzoforte on      MIDI Key 112
//       98:  -1:  Treble Mezzoforte off     MIDI Key 113
//		 

void RollOptions::setRollTypeLicenseeWelte(void) {
	m_rollType = "welte-licensee";
	m_minTrackerSpacingToPaperEdge = 1.6; // check
	m_rewindHole = 89;
	m_rewindHoleMidi = 104;
	m_trackerHoles = 98;

	m_bass_midi = 16;   // first MIDI Note on bass side of paper
	m_treble_midi = 113; // first MIDI Note on treble side of paper

	m_bassExpressionTrackStartNumberLeft = 1;
	m_bassExpressionTrackStartMidi = 16;
	m_bassNotesTrackStartNumberLeft = 9;
	m_bassNotesTrackStartMidi = 24;

	m_trebleNotesTrackStartNumberLeft = 52;
	m_trebleNotesTrackStartMidi = 67;

	m_trebleExpressionTrackStartNumberLeft = 89;
	m_trebleExpressionTrackStartMidi = 104;

	hasExpressionMidiFileSetup();
}



//////////////////////////////
//
// RollOptions::setRollTypeDuoArt -- Apply settings suitable for Aeolian Duo-Art piano rolls.
//
// Note that the snakebite holes are somewhat narrower than the other holes,
// and the rewind hole is wider.
//
// Duo-Art tracker holes:
//
//   9 expression/control columns on bass side (some empty):
//       1:  Rewind (wide hole)              MIDI Key 16
//       2:  Empty (overlaps with rewind)    MIDI Key 17
//       3:  Soft pedal                      MIDI Key 18
//       4:  Bass theme snakebite            MIDI Key 19
//       5:  Bass theme snakebite            MIDI Key 20
//       6:  Bass volume 1                   MIDI Key 21
//       7:  Bass volume 2                   MIDI Key 22
//       8:  Bass volume 4                   MIDI Key 23
//       9:  Bass volume 8                   MIDI Key 24
//   Then 80 notes from C#1 to G#7 (MIDI notes 25 to 104)
//       10: C#1                             MIDI Key 25
//       ...
//       48: D#4                             MIDI Key 63
//    Treble register:
//       49: E4                              MIDI Key 64
//       ...
//       89: G#7                             MIDI Key 104
//   9 expression columns on the treble side (some empty):
//       90: -9:  Treble volume 8            MIDI Key 105
//       91: -8:  Treble volume 4            MIDI Key 106
//       92: -7:  Treble volume 2            MIDI Key 107
//       93: -6:  Treble volume 1            MIDI Key 108
//       94: -5:  Treble theme snakebite     MIDI Key 109
//       95: -4:  Treble theme snakebite     MIDI Key 110
//       96: -3:  Blank                      MIDI Key 111
//       97: -2:  Blank                      MIDI Key 112
//       98: -1:  Sustain         pedal      MIDI Key 113
//		 

void RollOptions::setRollTypeDuoArt(void) {
	m_rollType = "duo-art";
	m_minTrackerSpacingToPaperEdge = 1.6; // check
	m_rewindHole = 1;
	m_rewindHoleMidi = 16;
	m_trackerHoles = 98;

	m_bass_midi = 16;   // first MIDI Note on bass side of paper
	m_treble_midi = 64; // first MIDI Note on treble side of paper

	m_bassExpressionTrackStartNumberLeft = 1;
	m_bassExpressionTrackStartMidi = 16;
	m_bassNotesTrackStartNumberLeft = 10;
	m_bassNotesTrackStartMidi = 25;

	m_trebleNotesTrackStartNumberLeft = 49;
	m_trebleNotesTrackStartMidi = 64;

	m_trebleExpressionTrackStartNumberLeft = 90;
	m_trebleExpressionTrackStartMidi = 105;

	hasExpressionMidiFileSetup();
}



//////////////////////////////
//
// RollOptions::setRollTypeAmpico -- Apply settings suitable for Ampico (A) piano rolls.
//
// Ampico (A) tracker holes:
//
//   7 expression holes on the bass side:
//       1:  Bass slow cresc                 MIDI Key 16
//       2:  Bass intensity 2                MIDI Key 17
//       3:  Soft pedal                      MIDI Key 18
//       4:  Bass intensity 4                MIDI Key 19
//       5:  Bass fast cresc                 MIDI Key 20
//       6:  Bass intensity 6                MIDI Key 21
//       7:  Bass intensity cancel           MIDI Key 22
//   Then 83 notes from B0 to A7 (MIDI notes 23 to 105)
//       8:  B0                              MIDI Key 23
//       ...
//       49: E4                              MIDI Key 64
//    Treble register:
//       50: F4                              MIDI Key 65
//       ...
//       90: A7                              MIDI Key 105
//   8 expression/control holes on the treble side:
//       91: -8:  Rewind                     MIDI Key 106
//       92: -7:  Treble intensity cancel    MIDI Key 107
//       93: -6:  Treble intensity 6         MIDI Key 108
//       94: -5:  Treble fast cresc          MIDI Key 109
//       95: -4:  Treble intensity 4         MIDI Key 110
//       96: -3:  Sustain pedal              MIDI Key 111
//       97: -2:  Treble intensity 2         MIDI Key 112
//       98: -1:  Treble slow cresc          MIDI Key 113
//		 

void RollOptions::setRollTypeAmpico(void) {
	m_rollType = "ampico";
	m_minTrackerSpacingToPaperEdge = 1.6; // check
	m_rewindHole = 91; // Beware of post-rewind patterns on recut rolls
	m_rewindHoleMidi = 106;
	m_trackerHoles = 98;

	m_bass_midi = 16;   // first MIDI Note on bass side of paper
	m_treble_midi = 65; // first MIDI Note on treble side of paper

	m_bassExpressionTrackStartNumberLeft = 1;
	m_bassExpressionTrackStartMidi = 16;
	m_bassNotesTrackStartNumberLeft = 8;
	m_bassNotesTrackStartMidi = 23;

	m_trebleNotesTrackStartNumberLeft = 50;
	m_trebleNotesTrackStartMidi = 65;

	m_trebleExpressionTrackStartNumberLeft = 91;
	m_trebleExpressionTrackStartMidi = 106;

	hasExpressionMidiFileSetup();
}



//////////////////////////////
//
// RollOptions::setRollTypeAmpicoB -- Apply settings suitable for Ampico (B) piano rolls.
//
// Ampico (B) tracker holes:
//
//   8 expression holes on the bass side:
//       1:  Amplifier trigger (B only)      MIDI Key 15
//       2:  Unused (A only)                 MIDI Key 16
//       3:  Bass intensity 2                MIDI Key 17
//       4:  Soft pedal                      MIDI Key 18
//       5:  Bass intensity 4                MIDI Key 19
//       6:  Unused (A only)                 MIDI Key 20
//       7:  Bass intensity 6                MIDI Key 21
//       8:  Bass intensity cancel           MIDI Key 22
//   Then 83 notes from B0 to A7 (MIDI notes 23 to 105)
//       9:  B0                              MIDI Key 23
//       ...
//       50: E4                              MIDI Key 64
//    Treble register:
//       51: F4                              MIDI Key 65
//       ...
//       91: A7                              MIDI Key 105
//   9 expression/control holes on the treble side:
//       92: -9:  Rewind                     MIDI Key 106
//       93: -8:  Treble intensity cancel    MIDI Key 107
//       94: -7:  Treble intensity 6         MIDI Key 108
//       95: -6:  Treble fast cresc          MIDI Key 109
//       96: -5:  Treble intensity 4         MIDI Key 110
//       97: -4:  Sustain pedal              MIDI Key 111
//       98: -3:  Treble intensity 2         MIDI Key 112
//       99: -2:  Treble slow cresc          MIDI Key 113
//      100: -1:  Sub intensity (B only)     MIDI Key 114
//

void RollOptions::setRollTypeAmpicoB(void) {
	m_rollType = "ampico_b";
	m_minTrackerSpacingToPaperEdge = 1.6; // check
	m_rewindHole = 92; // Beware of post-rewind patterns on recut rolls
	m_rewindHoleMidi = 106;
	m_trackerHoles = 100;

	m_bass_midi = 15;   // first MIDI Note on bass side of paper
	m_treble_midi = 65; // first MIDI Note on treble side of paper

	m_bassExpressionTrackStartNumberLeft = 1;
	m_bassExpressionTrackStartMidi = 15;
	m_bassNotesTrackStartNumberLeft = 9;
	m_bassNotesTrackStartMidi = 23;

	m_trebleNotesTrackStartNumberLeft = 51;
	m_trebleNotesTrackStartMidi = 65;

	m_trebleExpressionTrackStartNumberLeft = 92;
	m_trebleExpressionTrackStartMidi = 106;

	hasExpressionMidiFileSetup();
}



//////////////////////////////
//
// RollOptions::setRollType65Note -- Apply settings suitable for 65-note piano rolls.
//   * Aeolian "universal"
//   * 11.125" width
//   * 6 holes to the inch
//   * 4.23 mm /hole
//   * First bass hole centered about 107 pixels @ 300 DPI from bass edge.
//   * First treble hole centered about 98 pixels @ 300 DPI from bass edge.
//   * Punch widths about 31 pixels at 300 DPI.
//   * Paper width 3406 @ 300 DPI = 11.35 inches
//   * about 50 pixels between tracker bar holes
//   * Lowest note A1 (MIDI note 33)
//   * Highest note C#7 (MIDI note 97)
//   * No sustain pedal
//
//

void RollOptions::setRollType65Note(void) {
	m_rollType = "65-note";
	m_bridgeFactor  = 1.25;
	m_minTrackerSpacingToPaperEdge = 2.0;
	m_rewindHole = 0;  // no rewind hole
	m_rewindHoleMidi = 0;
	m_trackerHoles = 65;

	m_bass_midi   = 33; // first MIDI note/expression on bass side of paper
	m_treble_midi = 97; // first MIDI note/expression on treble side of paper

	// no bass expression
	m_bassExpressionTrackStartNumberLeft = 0;
	m_bassExpressionTrackStartMidi = 0;
	m_bassNotesTrackStartNumberLeft = 0;
	m_bassNotesTrackStartMidi = 0;

	// no treble expression
	m_trebleNotesTrackStartNumberLeft = 0;
	m_trebleNotesTrackStartMidi = 0;
	m_trebleExpressionTrackStartNumberLeft = 0;
	m_trebleExpressionTrackStartMidi = 0;

	hasNoExpressionMidiFileSetup();
}



//////////////////////////////
//
// RollOptions::setRollType88Note -- Apply settings suitable for 88-note piano rolls.
//   * Introduced in 1900
//   * United States standardized to 88 note scale in 1909
//   * 9 holes/inch
//   * 100 positions with 6 mostly empty slots on each edge (for expression)
//   * Pedal is at position 4, which is MIDI note 18
//   * 88 notes are A0 (MIDI 21) at position 7 though C7 (MIDI 108) at position 94.
//   * The notes are evenly centered on the roll, with the middle of the 88 notes
//     occurring at the middle of the paper (E4 is last note on bass half of paper,
//     and F4 is first note on treble half of paper.
//
//   Position     MIDI    Meaning
//   ==============================
//       1        15      unused
//       2        16      unused, sometimes rewind hole
//       3        17      unused
//       4        18      Sustain pedal
//       5        19      Bass snakebite accent
//       6        20      Bass snakebite accent
//       7        21      A0
//       ...
//       50       64      E4  Pretend Bass register
//       -------------------------
//       51       65      F4  Pretend Treble register
//       ...
//       94      108      C7
//       95      109      Treble snakebite accent
//       96      110      Treble snakebite accent
//       97      111      unused
//       98      112      unused
//       99      113      unused
//      100      114      unused
//

void RollOptions::setRollType88Note(void) {
	m_rollType = "88-note";
	m_bridgeFactor  = 0.85;
	m_minTrackerSpacingToPaperEdge = 1.3; // previously 1.6
	m_rewindHole = 0;  // no rewind hole (but can be at position 1, MIDI 16)
	m_rewindHoleMidi = 0;
	m_trackerHoles = 100;

	// m_bass_midi == first MIDI note/expression on bass side of paper.
	// This is the first tracker bar position on the roll (left side,
	// or bass side).
	m_bass_midi   = 15;  

	// m_treble_midi == first MIDI note/expression on the treble side of the paper.
	// This is the last tracker bar position on the roll (right side, or
	// treble side).
	m_treble_midi = 114; // first MIDI note/expression on treble side of paper

	// bass expression (sustain pedal and snakebite accents)
	m_bassExpressionTrackStartNumberLeft = 1;
	m_bassExpressionTrackStartMidi = 15;
	m_bassNotesTrackStartNumberLeft = 7;
	m_bassNotesTrackStartMidi = 21;

	// treble expression (not really used except for snakebite accents)
	m_trebleNotesTrackStartNumberLeft = 51;
	m_trebleNotesTrackStartMidi = 65;
	m_trebleExpressionTrackStartNumberLeft = 95;
	m_trebleExpressionTrackStartMidi = 109;

	hasExpressionMidiFileSetup();
}



/////////////////////////////////
//
// RollOptions::getRewindHoleNumber(void) -- returns 0 if unknown.
//

int RollOptions::getRewindHoleBassNumber(void) {
	return m_rewindHole;
}



/////////////////////////////////
//
// RollOptions::getRewindHoleLeftIndex(void) -- returns 0 if unknown.
//

int RollOptions::getRewindHoleBassIndex(void) {
	return m_rewindHole - 1;
}



/////////////////////////////////
//
// RollOptions::getRewindHoleMidi(void) -- returns 0 if unknown; otherwise,
//     returns the MIDI note number of the rewind hole.
//

int RollOptions::getRewindHoleMidi(void) {
	return m_rewindHoleMidi;
}



/////////////////////////////////
//
// RollOptions::getBridgeFactor(void) -- Returns the ratio of width to length
//     distance which will force the merging of adjacent holes.
//

double RollOptions::getBridgeFactor(void) {
	return m_bridgeFactor;
}



//////////////////////////////
//
// RollOptions::getExpectedTrackerHoleCount -- Returns 0 if roll type is undefined.
//

int RollOptions::getExpectedTrackerHoleCount(void) {
	return m_trackerHoles;
}



//////////////////////////////
//
// RollOptions::setThreshold -- 
//

void RollOptions::setThreshold(int value) {
	m_threshold = value;
}



//////////////////////////////
//
// RollOptions::getThreshold -- 
//

int RollOptions::getThreshold(void) {
	return (ucharint)m_threshold;
}



//////////////////////////////
//
// RollOptions::setRollAcceleration -- 
//

void RollOptions::setRollAcceleration(double value) {
	m_rollAcceleration = value;
}



//////////////////////////////
//
// RollOptions::getRollAcceleration -- 
//

double RollOptions::getRollAcceleration(void) {
	return m_rollAcceleration;
}



//////////////////////////////
//
// RollOptions::hasNoExpressionMidiFileSetup -- The roll has no 
//   expression, so the output MIDI files will contain two
//   tracks: the 0th track is the tempo and metadata track with no
//   notes, and the 1st track contains all of the notes from the roll.
//

void RollOptions::hasNoExpressionMidiFileSetup(void) { 
	// MIDI file track assignments (offset from 0, with track 0 note having no notes):
	m_bass_track       = 1;
	m_treble_track     = 1;
	m_bass_exp_track   = 1;
	m_treble_exp_track = 1;

	// MIDI file channel assignments for each track, (offset from 0):
	m_bass_exp_ch      = 0;
	m_bass_ch          = 0;
	m_treble_ch        = 0;
	m_treble_exp_ch    = 0;
}



//////////////////////////////
//
// RollOptions::hasExpressionMidiFileSetup --  The roll has expression, so the output
//     MIDI files will contain two tracks: the 0th track is the tempo and metadata
//     track with no notes, the 1st track contains the bass notes, the 2nd track
//     contains the treble notes, the 3rd track contains the bass expression, and
//     the fourth track contains the treble expression.
//

void RollOptions::hasExpressionMidiFileSetup(void) {
	// MIDI file track assignments (offset from 0, with track 0 note having notes):
	m_bass_track       = 1;
	m_treble_track     = 2;
	m_bass_exp_track   = 3;
	m_treble_exp_track = 4;

	// MIDI file channel assignments for each track, (offset from 0):
	m_bass_exp_ch      = 0;
	m_bass_ch          = 1;
	m_treble_ch        = 2;
	m_treble_exp_ch    = 3;
}



} // end rip namespace




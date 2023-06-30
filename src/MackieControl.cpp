#include "MackieControl.h"

namespace mackieControl {
	Message::Message(const juce::MidiMessage& midiMessage)
		: message(midiMessage) {
	}
}

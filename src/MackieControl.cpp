#include "MackieControl.h"

namespace mackieControl {
	Message::Message(const juce::MidiMessage& midiMessage)
		: message(midiMessage) {}

	Message::Message(const Message& message) 
		: message(message.message) {}

	Message::Message(Message&& message) noexcept
		: message(std::move(message.message)) {}

	Message& Message::operator=(const Message& message) {
		if (this != &message) {
			this->message = message.message;
		}
		return *this;
	}

	Message& Message::operator=(Message&& message) noexcept {
		if (this != &message) {
			this->message = std::move(message.message);
		}
		return *this;
	}

	bool Message::isSysEx() const {
		if (this->message.isSysEx()) {
			if (this->message.getSysExDataSize() >= 5) {
				auto ptrData = this->message.getSysExData();
				return isValidSysExMessage(ptrData[4]);
			}
		}
		return false;
	}

	bool Message::isNote() const {
		if (this->message.isNoteOnOrOff()) {
			return isValidNoteMessage(this->message.getNoteNumber()) &&
				isValidVelocityMessage(this->message.getVelocity());
		}
		return false;
	}

	bool Message::isCC() const {
		if (this->message.isController()) {
			return isValidCCMessage(this->message.getControllerNumber());
		}
		return false;
	}

	bool Message::isPitchWheel() const {
		if (this->message.isPitchWheel()) {
			auto channel = this->message.getChannel();
			return channel >= 1 && channel <= 9;
		}
		return false;
	}

	bool Message::isChannelPressure() const {
		if (this->message.isChannelPressure()) {
			return true;
		}
		return false;
	}

	bool Message::isMackieControl() const {
		return this->isSysEx() ||
			this->isNote() ||
			this->isCC() ||
			this->isPitchWheel() ||
			this->isChannelPressure();
	}
}

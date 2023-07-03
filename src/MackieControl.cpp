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

	Message& Message::operator=(const juce::MidiMessage& message) {
		this->message = message;
		return *this;
	}

	juce::MidiMessage Message::toMidi() const {
		return this->message;
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

	Message Message::fromMidi(const juce::MidiMessage& message) {
		return Message{ message };
	}

	juce::MidiMessage Message::toMidi(const Message& message) {
		return message.toMidi();
	}

	Message Message::createNote(NoteMessage type, VelocityMessage vel) {
		return Message{ juce::MidiMessage::noteOn(1, static_cast<int>(type), static_cast<uint8_t>(vel)) };
	}

	Message Message::createCC(CCMessage type, int value) {
		return Message{ juce::MidiMessage::controllerEvent(1, static_cast<int>(type), static_cast<int>(value)) };
	}

	Message Message::createPitchWheel(int channel, int value) {
		return Message{ juce::MidiMessage::pitchWheel(channel, value) };
	}

	Message Message::createChannelPressure(int channel, int value) {
		return Message{ juce::MidiMessage::channelPressureChange(1, (channel - 1) * 16 + value) };
	}
}

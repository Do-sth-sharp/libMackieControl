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

	Message Message::createDeviceQuery() {
		uint8_t bytes[5] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::DeviceQuery);

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createHostConnectionQuery(uint8_t serialNum[7], uint32_t challengeCode) {
		uint8_t bytes[5 + 7 + sizeof(challengeCode)] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::HostConnectionQuery);
		std::memcpy(&bytes[5], serialNum, 7);
		std::memcpy(&bytes[5 + 7], &challengeCode, sizeof(challengeCode));

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createHostConnectionReply(uint8_t serialNum[7], uint32_t responseCode) {
		uint8_t bytes[5 + 7 + sizeof(responseCode)] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::HostConnectionReply);
		std::memcpy(&bytes[5], serialNum, 7);
		std::memcpy(&bytes[5 + 7], &responseCode, sizeof(responseCode));

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createHostConnectionConfirmation(uint8_t serialNum[7]) {
		uint8_t bytes[5 + 7] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::HostConnectionConfirmation);
		std::memcpy(&bytes[5], serialNum, 7);

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createHostConnectionError(uint8_t serialNum[7]) {
		uint8_t bytes[5 + 7] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::HostConnectionError);
		std::memcpy(&bytes[5], serialNum, 7);

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createLCDBackLightSaver(uint8_t state, uint8_t timeout) {
		if (state > 0) {
			uint8_t bytes[5 + 2] = {};
			bytes[4] = static_cast<uint8_t>(SysExMessage::LCDBackLightSaver);
			bytes[5] = state;
			bytes[6] = timeout;

			return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
		}
		
		uint8_t bytes[5 + 1] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::LCDBackLightSaver);
		bytes[5] = state;

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createTouchlessMovableFaders(uint8_t state) {
		uint8_t bytes[5 + 1] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::TouchlessMovableFaders);
		bytes[5] = state;

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createFaderTouchSensitivity(uint8_t channelNumber, uint8_t value) {
		uint8_t bytes[5 + 2] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::FaderTouchSensitivity);
		bytes[5] = channelNumber;
		bytes[6] = value;

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createGoOffline() {
		uint8_t bytes[5] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::GoOffline);

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createTimeCodeBBTDisplay(uint8_t* data, int size) {
		int byteSize = 5 + 1 + size + 1;
		auto bytes = std::unique_ptr<uint8_t[]>(new uint8_t[byteSize]());

		bytes[4] = static_cast<uint8_t>(SysExMessage::TimeCodeBBTDisplay);
		std::memcpy(&bytes[6], data, size);

		return Message{ juce::MidiMessage::createSysExMessage(bytes.get(), byteSize) };
	}

	Message Message::createAssignment7SegmentDisplay(uint8_t data[2]) {
		uint8_t bytes[5 + 1 + 2] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::Assignment7SegmentDisplay);
		std::memcpy(&bytes[6], data, 2);

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createLCD(uint8_t place, char* data, int size) {
		int byteSize = 5 + 1 + size;
		auto bytes = std::unique_ptr<uint8_t[]>(new uint8_t[byteSize]());

		bytes[4] = static_cast<uint8_t>(SysExMessage::LCD);
		bytes[5] = place;
		std::memcpy(&bytes[6], data, size);

		return Message{ juce::MidiMessage::createSysExMessage(bytes.get(), byteSize) };
	}

	Message Message::createVersionRequest() {
		uint8_t bytes[5] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::VersionRequest);

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createVersionReply(char* data, int size) {
		int byteSize = 5 + 1 + size;
		auto bytes = std::unique_ptr<uint8_t[]>(new uint8_t[byteSize]());

		bytes[4] = static_cast<uint8_t>(SysExMessage::VersionReply);
		std::memcpy(&bytes[6], data, size);

		return Message{ juce::MidiMessage::createSysExMessage(bytes.get(), byteSize) };
	}

	Message Message::createChannelMeterMode(uint8_t channelNumber, uint8_t mode) {
		uint8_t bytes[5 + 2] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::ChannelMeterMode);
		bytes[5] = channelNumber;
		bytes[6] = mode;

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createGlobalLCDMeterMode(uint8_t mode) {
		uint8_t bytes[5 + 1] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::GlobalLCDMeterMode);
		bytes[5] = mode;

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createAllFaderstoMinimum() {
		uint8_t bytes[5] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::AllFaderstoMinimum);

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createAllLEDsOff() {
		uint8_t bytes[5] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::AllLEDsOff);

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createReset() {
		uint8_t bytes[5] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::Reset);

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
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

	uint8_t Message::charToMackie(char c) {
		if (c >= 'a' && c <= 'z') { return static_cast<uint8_t>((c - 'a') + 1); }
		else if (c >= 'A' && c <= 'Z') { return static_cast<uint8_t>((c - 'A') + 1); }
		else if (c >= '0' && c <= '9') { return static_cast<uint8_t>((c - '0') + 0x30); }

		return 0x20;
	}

	uint8_t Message::toLCDPlace(bool lowerLine, uint8_t index) {
		return (lowerLine ? 56Ui8 : 0Ui8) + index;
	}

	uint8_t Message::toChannelMeterMode(
		bool signalLEDEnabled, bool peakHoldDisplayEnabled, bool LCDLevelMeterEnabled) {
		return (static_cast<uint8_t>(signalLEDEnabled) << 0)
			+ (static_cast<uint8_t>(peakHoldDisplayEnabled) << 1)
			+ (static_cast<uint8_t>(LCDLevelMeterEnabled) << 2);
	}

	int Message::toVPotValue(WheelType type, int ticks) {
		return static_cast<int>(type) * 64 + ticks;
	}

	int Message::toVPotLEDRingValue(bool centerLEDOn, VPotLEDRingMode mode, int value) {
		return static_cast<int>(centerLEDOn) * 64
			+ static_cast<int>(mode) * 16
			+ value;
	}

	int Message::toJogWheelValue(WheelType type, int ticks) {
		return static_cast<int>(type) * 64 + ticks;
	}
}

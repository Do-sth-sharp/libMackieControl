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

	std::tuple<SysExMessage> Message::getSysExData() const {
		if (this->message.getSysExDataSize() < 5) { return { static_cast<SysExMessage>(-1) }; }
		return { static_cast<SysExMessage>(this->message.getSysExData()[4]) };
	}

	std::tuple<std::array<uint8_t, 7>, uint32_t> Message::getHostConnectionQueryData() const {
		if (this->message.getSysExDataSize() <
			5 + sizeof(std::array<uint8_t, 7>) + sizeof(uint32_t)) { return std::tuple<std::array<uint8_t, 7>, uint32_t>{}; }

		std::array<uint8_t, 7> bytes;
		std::memcpy(bytes.data(), &(this->message.getSysExData()[5]), sizeof(bytes));

		return { bytes, static_cast<uint32_t>(this->message.getSysExData()[5 + sizeof(bytes)]) };
	}

	std::tuple<std::array<uint8_t, 7>, uint32_t> Message::getHostConnectionReplyData() const {
		if (this->message.getSysExDataSize() <
			5 + sizeof(std::array<uint8_t, 7>) + sizeof(uint32_t)) {
			return std::tuple<std::array<uint8_t, 7>, uint32_t>{};
		}

		std::array<uint8_t, 7> bytes;
		std::memcpy(bytes.data(), &(this->message.getSysExData()[5]), sizeof(bytes));

		return { bytes, static_cast<uint32_t>(this->message.getSysExData()[5 + sizeof(bytes)]) };
	}

	std::tuple<std::array<uint8_t, 7>> Message::getHostConnectionConfirmationData() const {
		if (this->message.getSysExDataSize() < 5 + sizeof(std::array<uint8_t, 7>)) {
			return std::tuple<std::array<uint8_t, 7>>{};
		}

		std::array<uint8_t, 7> bytes;
		std::memcpy(bytes.data(), &(this->message.getSysExData()[5]), sizeof(bytes));

		return { bytes };
	}

	std::tuple<std::array<uint8_t, 7>> Message::getHostConnectionErrorData() const {
		if (this->message.getSysExDataSize() < 5 + sizeof(std::array<uint8_t, 7>)) {
			return std::tuple<std::array<uint8_t, 7>>{};
		}

		std::array<uint8_t, 7> bytes;
		std::memcpy(bytes.data(), &(this->message.getSysExData()[5]), sizeof(bytes));

		return { bytes };
	}

	std::tuple<uint8_t, uint8_t> Message::getLCDBackLightSaverData() const {
		if (this->message.getSysExDataSize() < 5 + 1) {
			return std::tuple<uint8_t, uint8_t>{};
		}

		return { static_cast<uint8_t>(this->message.getSysExData()[5]),
			(this->message.getSysExDataSize() >= 7) ? static_cast<uint8_t>(this->message.getSysExData()[6]) : 0 };
	}

	std::tuple<uint8_t> Message::getTouchlessMovableFadersData() const {
		if (this->message.getSysExDataSize() < 5 + 1) {
			return std::tuple<uint8_t>{};
		}

		return { static_cast<uint8_t>(this->message.getSysExData()[5]) };
	}

	std::tuple<uint8_t, uint8_t> Message::getFaderTouchSensitivityData() const {
		if (this->message.getSysExDataSize() < 5 + 2) {
			return std::tuple<uint8_t, uint8_t>{};
		}

		return { static_cast<uint8_t>(this->message.getSysExData()[5]),
			static_cast<uint8_t>(this->message.getSysExData()[6]) };
	}

	std::tuple<const uint8_t*, int> Message::getTimeCodeBBTDisplayData() const {
		if (this->message.getSysExDataSize() < 5 + 1 + 1 + 1) {
			return std::tuple<uint8_t*, int>{};
		}

		return { &(this->message.getSysExData()[6]),
			this->message.getSysExDataSize() - 1 - 6 };
	}

	std::tuple<std::array<uint8_t, 2>> Message::getAssignment7SegmentDisplayData() const {
		if (this->message.getSysExDataSize() < 5 + 1 + sizeof(std::array<uint8_t, 2>)) {
			return std::tuple<std::array<uint8_t, 2>>{};
		}

		std::array<uint8_t, 2> bytes;
		std::memcpy(bytes.data(), &(this->message.getSysExData()[6]), sizeof(bytes));

		return { bytes };
	}

	std::tuple<uint8_t, const char*, int> Message::getLCDData() const {
		if (this->message.getSysExDataSize() < 5 + 1 + 1) {
			return std::tuple<uint8_t, char*, int>{};
		}

		return { static_cast<uint8_t>(this->message.getSysExData()[5]),
			reinterpret_cast<const char*>(&(this->message.getSysExData()[6])) ,
			this->message.getSysExDataSize() - 6 };
	}

	std::tuple<const char*, int> Message::getVersionReplyData() const {
		if (this->message.getSysExDataSize() < 5 + 1 + 1) {
			return std::tuple<char*, int>{};
		}

		return { reinterpret_cast<const char*>(&(this->message.getSysExData()[6])) ,
			this->message.getSysExDataSize() - 6 };
	}

	std::tuple<uint8_t, uint8_t> Message::getChannelMeterModeData() const {
		if (this->message.getSysExDataSize() < 5 + 2) {
			return std::tuple<uint8_t, uint8_t>{};
		}

		return { static_cast<uint8_t>(this->message.getSysExData()[5]),
			static_cast<uint8_t>(this->message.getSysExData()[6]) };
	}

	std::tuple<uint8_t> Message::getGlobalLCDMeterModeData() const {
		if (this->message.getSysExDataSize() < 5 + 1) {
			return std::tuple<uint8_t>{};
		}

		return { static_cast<uint8_t>(this->message.getSysExData()[5]) };
	}

	std::tuple<NoteMessage, VelocityMessage> Message::getNoteData() const {
		return { static_cast<NoteMessage>(this->message.getNoteNumber()),
			static_cast<VelocityMessage>(this->message.getVelocity()) };
	}

	std::tuple<CCMessage, int> Message::getCCData() const {
		return { static_cast<CCMessage>(this->message.getControllerNumber()),
			this->message.getControllerValue() };
	}

	std::tuple<int, int> Message::getPitchWheelData() const {
		return { this->message.getChannel(),
			this->message.getPitchWheelValue() };
	}

	std::tuple<int, int> Message::getChannelPressureData() const {
		int value = this->message.getChannelPressureValue();
		return { value / 16 + 1,value % 16 };
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

	Message Message::createHostConnectionQuery(const std::array<uint8_t, 7>& serialNum, uint32_t challengeCode) {
		uint8_t bytes[5 + sizeof(serialNum) + sizeof(challengeCode)] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::HostConnectionQuery);
		std::memcpy(&bytes[5], serialNum.data(), sizeof(serialNum));
		std::memcpy(&bytes[5 + sizeof(serialNum)], &challengeCode, sizeof(challengeCode));

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createHostConnectionReply(const std::array<uint8_t, 7>& serialNum, uint32_t responseCode) {
		uint8_t bytes[5 + sizeof(serialNum) + sizeof(responseCode)] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::HostConnectionReply);
		std::memcpy(&bytes[5], serialNum.data(), sizeof(serialNum));
		std::memcpy(&bytes[5 + sizeof(serialNum)], &responseCode, sizeof(responseCode));

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createHostConnectionConfirmation(const std::array<uint8_t, 7>& serialNum) {
		uint8_t bytes[5 + sizeof(serialNum)] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::HostConnectionConfirmation);
		std::memcpy(&bytes[5], serialNum.data(), sizeof(serialNum));

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createHostConnectionError(const std::array<uint8_t, 7>& serialNum) {
		uint8_t bytes[5 + sizeof(serialNum)] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::HostConnectionError);
		std::memcpy(&bytes[5], serialNum.data(), sizeof(serialNum));

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

	Message Message::createTimeCodeBBTDisplay(const uint8_t* data, int size) {
		int byteSize = 5 + 1 + size + 1;
		auto bytes = std::unique_ptr<uint8_t[]>(new uint8_t[byteSize]());

		bytes[4] = static_cast<uint8_t>(SysExMessage::TimeCodeBBTDisplay);
		std::memcpy(&bytes[6], data, size);

		return Message{ juce::MidiMessage::createSysExMessage(bytes.get(), byteSize) };
	}

	Message Message::createAssignment7SegmentDisplay(const std::array<uint8_t, 2>& data) {
		uint8_t bytes[5 + 1 + sizeof(data)] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::Assignment7SegmentDisplay);
		std::memcpy(&bytes[6], data.data(), sizeof(data));

		return Message{ juce::MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createLCD(uint8_t place, const char* data, int size) {
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

	Message Message::createVersionReply(const char* data, int size) {
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
		if (c >= 'a' && c <= 'z') { return (c - 'a') + 1; }
		else if (c >= 'A' && c <= 'Z') { return (c - 'A') + 1; }
		else if (c >= '0' && c <= '9') { return c; }

		return ' ';
	}

	char Message::mackieToChar(uint8_t c) {
		if ((c - 1) >= 0 && (c - 1) <= 'Z' - 'A') { return 'A' + (c - 1); }
		else if (c >= '0' && c <= '9') { return c; }

		return ' ';
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

	std::tuple<bool, uint8_t> Message::convertLCDPlace(uint8_t place) {
		return { place >= 56, (place >= 56) ? (place - 56Ui8) : place };
	}

	std::tuple<bool, bool, bool> Message::convertChannelMeterMode(uint8_t mode) {
		return { mode & (1 << 0),
			mode & (1 << 1),
			mode & (1 << 2) };
	}

	std::tuple<WheelType, int> Message::convertVPotValue(int value) {
		return { static_cast<WheelType>(value / 64), value % 64 };
	}

	std::tuple<bool, VPotLEDRingMode, int> Message::convertVPotLEDRingValue(int value) {
		return { static_cast<bool>(value / 64), static_cast<VPotLEDRingMode>((value % 64) / 16), value % 16 };
	}

	std::tuple<WheelType, int> Message::convertJogWheelValue(int value) {
		return { static_cast<WheelType>(value / 64), value % 64 };
	}
}

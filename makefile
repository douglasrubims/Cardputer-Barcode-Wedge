# Configuration
PROJECT_NAME = Cardputer-Barcode-Wedge
FQBN = esp32:esp32:m5stack_cardputer
PORT = /dev/cu.usbmodem11301
BAUD = 115200

# Project directory (where the .ino file is located)
SRC_DIR = .

# Main rules
all: compile upload

compile:
	arduino-cli compile --fqbn $(FQBN) $(SRC_DIR)

upload:
	arduino-cli upload -p $(PORT) --fqbn $(FQBN) $(SRC_DIR)

monitor:
	arduino-cli monitor -p $(PORT) -c baudrate=$(BAUD)

clean:
	rm -rf $(SRC_DIR)/build

# Help
help:
	@echo "Available commands:"
	@echo "  make compile   -> Compile the project"
	@echo "  make upload    -> Upload code to the Cardputer"
	@echo "  make all       -> Compile and upload"
	@echo "  make monitor   -> Open serial monitor"
	@echo "  make clean     -> Clean build folder"

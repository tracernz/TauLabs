"use strict;"

function BoardType(board) {
	var self = this;

	Object.keys(board).forEach(function(prop) {
		self[prop] = board[prop];
	});
}

BoardType.prototype.matchesFilter = function(filter) {
	var self = this;

	return Object.keys(filter).every(function(prop) {
		if(!self.hasOwnProperty(prop))
			return false;
		if(self[prop] != filter[prop])
			return false;
		return true;
	});
};

BoardType.prototype.hasTauBootloader = function() {
	return this.flashLayout.hasOwnProperty("bootloaderBase");
}

BoardType.prototype.hasFlashEeprom = function() {
	return this.flashLayout.hasOwnProperty("eepromBase");
}

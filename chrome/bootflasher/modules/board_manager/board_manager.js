"use strict;"

function BoardManager() {
	var self = this;

	self.boards = [];

	self.boardList.forEach(function(board) {
		console.assert(board.hasOwnProperty("shortName"), "[BoardManager] shortName missing!");
		console.assert(board.hasOwnProperty("name"), "[BoardManager] name missing!");
		console.assert(board.hasOwnProperty("boardType"), "[BoardManager] boardType missing!");
		self.boards.push(new BoardType(board));
	});

	console.log("[BoardManager] %d boards loaded.", self.boards.length);
}

// Returns first board found matching filter
BoardManager.prototype.getBoard = function(filter) {
	for(var i = 0; i < this.boards.length; i++) {
		if(this.boards[i].matchesFilter(filter))
			return this.boards[i];
	}

	return null;
};

// Returns all boards found matching filter
BoardManager.prototype.getBoards = function(filter) {
	var result = [];

	for(var i = 0; i < this.boards.length; i++) {
		if(this.boards[i].matchesFilter(filter))
			result.push(this.boards[i]);
	}

	return result;
};

// Returns all boards found NOT matching filter
BoardManager.prototype.excludeBoards = function(filter) {
	var result = [];

	for(var i = 0; i < this.boards.length; i++) {
		if(!this.boards[i].matchesFilter(filter))
			result.push(this.boards[i]);
	}

	return result;
};

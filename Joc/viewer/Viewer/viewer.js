// *********************************************************************
// Global variables
// *********************************************************************

// Viewer state.
var curRound = 0;        // Current round index.
var gameDirection = 1;
var gameAnim    = true;
var gamePaused  = true;
var gamePreview = false; // If true, render will be called for the
			 // next tick even if game is paused, and then
			 // will be set to false.


// Data.
var raw_data_str;       // String for storing the raw data.
var dataLoaded = false; // Set to true when raw_data_str is ready to be parsed.
var data = { }          // Object for storing all the game data.


// Animation.
var frames_per_round = 16;
var speed            = 50;  // Ticks per second.
var frames           = 0;   // Incremented each tick, when it reaches
			    // frames_per_round, curRound is updated
			    // (acording to gameDirection).


// Visuals.
var unitSize = 0.6; // 1 = same size as tile.
var unitLineWidth = 2;

var  grid_color = "f8e1c1";
var water_color = "b5ffff";

var bonus_colors = {
    's': "7a716c",  // seed
    'l': "59bb01",  // leaf
    'b': "f9a102"   // bread
}

var player_colors = {
    0: "008000",
    1: "ff0000",
    2: "ffba00",
    3: "bf00ff"    
}

var dir = {
    0: "SE",
    1: "S",
    2: "SW",
    3: "W",
    4: "NW",
    5: "N",
    6: "NE",
    7: "E"
}

var diri = {
    0:  1, // SE
    1:  1, // S
    2:  1, // SW
    3:  0, // W
    4: -1, // NW
    5: -1, // N
    6: -1, // NE
    7:  0  // E
}

var dirj = {
    0:  1, // SE
    1:  0, // S
    2: -1, // SW
    3: -1, // W
    4: -1, // NW
    5:  0, // N
    6:  1, // NE
    7:  1  // E
}

// *********************************************************************
// Utility functions
// *********************************************************************

function getURLParameter (name) {
    // http://stackoverflow.com/questions/1403888/get-url-parameter-with-jquery
    var a = (RegExp(name + '=' + '(.+?)(&|$)').exec(location.search)||[,null])[1]
    if (a != null) return decodeURI(a);
    return null;
}


// Callback has a single parameter with the file contents.
function loadFile (file, callback) {
    var xmlhttp;

    if (file == null || file == "") {
	alert("You must specify a file to load.");
	return;
    }

    if (window.XMLHttpRequest) xmlhttp = new XMLHttpRequest();
    // Code for IE7+, Firefox, Chrome, Opera, Safari.

    else xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
    // Code for IE6, IE5.

    // http://www.w3schools.com/ajax/ajax_xmlhttprequest_onreadystatechange.asp
    xmlhttp.onreadystatechange = function() {
	// Note: We cannot check xmlhttp.status != 200 for errors
	// because status is not set when loading local files.
	if (xmlhttp.readyState == 4) callback(xmlhttp.responseText);
    }

    xmlhttp.open("GET", file, false);
    xmlhttp.send();
}


function int (s) {
    return parseInt(s);
}


function double (s) {
    return parseFloat(s);
}


function parse_assert (read_value, expected_value) {
    var correct = (read_value == expected_value);
    if (!correct)
	alert("Error parsing file, expected token: " + expected_value
	      + ", read token: " + read_value + ".");
    return correct;
}


// *********************************************************************
// Initialization functions
// *********************************************************************

function parseData (raw_data_str) {
    if (raw_data_str == "") {
	alert("Could not load game file.");
	return false;
    }

    // Convert text to tokens.
    var st = raw_data_str + "";
    var t = st.replace('\n', ' ').split(/\s+/);
    var p = 0;

    data.secgame = (t[p++] == "SecGame");

    parse_assert(t[p++], "Seed");
    data.seed = int(t[p++]);

    // Game and version.
    if (t[p++] != "Ants") {
	alert("Are you sure this is an Ants game file?");
	document.getElementById('file').value = "";
	document.getElementById('inputdiv'  ).style.display = "";
	document.getElementById('loadingdiv').style.display = "none";
	return false;
    }

    data.version = t[p++];
    if (data.version != "1.0")
	alert("Unsupported game version! Trying to load it anyway.");

    parse_assert(t[p++], "NUM_PLAYERS"); data.num_players = int(t[p++]);
    parse_assert(t[p++], "NUM_ROUNDS" ); data.num_rounds  = int(t[p++]);
    parse_assert(t[p++], "BOARD_ROWS" ); data.rows        = int(t[p++]);
    parse_assert(t[p++], "BOARD_COLS" ); data.cols        = int(t[p++]);

    // Ignore the rest of settings: not rellevant for visualitzation.
    parse_assert(t[p++], "QUEEN_PERIOD"    ); p++;
    parse_assert(t[p++], "SOLDIER_CARBO"   ); p++;
    parse_assert(t[p++], "SOLDIER_PROTE"   ); p++;
    parse_assert(t[p++], "SOLDIER_LIPID"   ); p++;
    parse_assert(t[p++], "WORKER_CARBO"	   ); p++;
    parse_assert(t[p++], "WORKER_PROTE"	   ); p++;
    parse_assert(t[p++], "WORKER_LIPID"	   ); p++;
    parse_assert(t[p++], "BREAD_CARBO"	   ); p++;
    parse_assert(t[p++], "BREAD_PROTE"	   ); p++;
    parse_assert(t[p++], "BREAD_LIPID"	   ); p++;
    parse_assert(t[p++], "SEED_CARBO"	   ); p++;
    parse_assert(t[p++], "SEED_PROTE"	   ); p++;
    parse_assert(t[p++], "SEED_LIPID"	   ); p++;
    parse_assert(t[p++], "LEAF_CARBO"	   ); p++;
    parse_assert(t[p++], "LEAF_PROTE"	   ); p++;
    parse_assert(t[p++], "LEAF_LIPID"	   ); p++;
    parse_assert(t[p++], "NUM_INI_SOLDIERS"); p++;
    parse_assert(t[p++], "NUM_INI_WORKERS" ); p++;
    parse_assert(t[p++], "BONUS_ROWS"	   ); p++;
    parse_assert(t[p++], "BONUS_COLS"	   ); p++;
    parse_assert(t[p++], "BONUS_PERIOD"    ); p++;
    parse_assert(t[p++], "WORKER_LIFE"     ); p++;
    parse_assert(t[p++], "SOLDIER_LIFE"    ); p++;
    parse_assert(t[p++], "QUEEN_LIFE"      ); p++;

    parse_assert(t[p++], "names");
    data.names = new Array();
    for (var i = 0; i < data.num_players; ++i) data.names[i] = t[p++];

    data.rounds = new Array();
    for (var round = 0; round <= data.num_rounds; ++round) {

	// Grid.

	p++; // 1st line of column labels.
        p++; // 2nd line of column labels.

	data.rounds[round] = new Object();
	data.rounds[round].rows = new Array();
	for (var i = 0; i < data.rows; ++i) {
	    parse_assert(t[p++], i);              // Row label.
	    data.rounds[round].rows[i] = t[p++];  // Row.
	}

	parse_assert(t[p++], "rivers");
	data.rivers = new Array();
	data.rivers.length = int(t[p++]);
	for (var i = 0; i < data.rivers.length; ++i) {
	    data.rivers[i] = new Array();
	    data.rivers[i].length = int(t[p++]);
	    for (var j = 0; j < data.rivers[i].length; ++j) {
		data.rivers[i][j] = new Object();
		data.rivers[i][j].i = int(t[p++]);
		data.rivers[i][j].j = int(t[p++]);
	    }
	}

	// Ignore the rectangles where food is generated.
	// For each kind of food and player, there are 2 numbers.
	parse_assert(t[p++], "bread"); p += 2*data.num_players;
	parse_assert(t[p++], "seed" ); p += 2*data.num_players;
	parse_assert(t[p++], "leaf" ); p += 2*data.num_players;

	// Round.
	parse_assert(t[p++], "round");
	if (int(t[p++]) != round) alert("Wrong round number!");

	// Score.
	parse_assert(t[p++], "score");
	data.rounds[round].score = new Array();
	for (var i = 0; i < data.num_players; ++i)
	    data.rounds[round].score[i] = int(t[p++]);

	// Status.
	parse_assert(t[p++], "status");
	data.rounds[round].cpu = new Array();
	for (var i = 0; i < data.num_players; ++i) {
	    var cpu = int(double(t[p++])*100);
	    data.rounds[round].cpu[i] = (cpu == -100) ? "out" : cpu + "%";
	}

	// Ants.
	parse_assert(t[p++], "ants");
	data.rounds[round].num_ants = int(t[p++]);

	parse_assert(t[p++], "type"  );
	parse_assert(t[p++], "id"    );
	parse_assert(t[p++], "player");
	parse_assert(t[p++], "i"     );
	parse_assert(t[p++], "j"     );
	parse_assert(t[p++], "carbo" );
	parse_assert(t[p++], "prote" );
	parse_assert(t[p++], "lipid" );
        parse_assert(t[p++], "bonus" );
        parse_assert(t[p++], "life" );

	data.rounds[round].carbo = { 0:0, 1:0, 2:0, 3:0 };
	data.rounds[round].prote = { 0:0, 1:0, 2:0, 3:0 };
	data.rounds[round].lipid = { 0:0, 1:0, 2:0, 3:0 };

	data.rounds[round].ants = new Array();
	for (var i = 0; i < data.rounds[round].num_ants; ++i) {
	    var type   =     t[p++];
	    var id     = int(t[p++]);
	    var player = int(t[p++]);
	    data.rounds[round].ants[id] = new Object();
	    data.rounds[round].ants[id].type   = type;
	    data.rounds[round].ants[id].id     = id;
	    data.rounds[round].ants[id].player = player;
	    data.rounds[round].ants[id].i      = int(t[p++]);
	    data.rounds[round].ants[id].j      = int(t[p++]);

	    if (type == 'q') {
		data.rounds[round].carbo[player] = int(t[p++]);
		data.rounds[round].prote[player] = int(t[p++]);
		data.rounds[round].lipid[player] = int(t[p++]);
	    }
	    else p += 3;

	    data.rounds[round].ants[id].bonus  = t[p++];
	    data.rounds[round].ants[id].life   = int(t[p++]);
	    
	    data.rounds[round].ants[id].c_type = '_';
	    data.rounds[round].ants[id].dir    = '_';
	    data.rounds[round].ants[id].a_type = '_';
	}

	if (round != data.num_rounds) {
	    // Commands.
	    parse_assert(t[p++], "commands");
	    var id = int(t[p++]);
	    while (id != -1) {
		data.rounds[round].ants[id].c_type = t[p++];
		data.rounds[round].ants[id].dir    = t[p++];
		data.rounds[round].ants[id].a_type = t[p++];
		id = int(t[p++]);
	    }
	}

	// Computing orientation.
	for (var id in data.rounds[round].ants) {
	    if (data.rounds[round].ants[id].c_type == 'm') {
		var dir = data.rounds[round].ants[id].dir;
		if      (dir == 'd')  data.rounds[round].ants[id].deg = 180;
		else if (dir == 'r')  data.rounds[round].ants[id].deg =  90;
		else if (dir == 'u')  data.rounds[round].ants[id].deg =   0;
		else if (dir == 'l')  data.rounds[round].ants[id].deg = 270;
		else if (round > 0 && data.rounds[round-1].ants[id] != null)
		    data.rounds[round].ants[id].deg = data.rounds[round-1].ants[id].deg;
		else
		    data.rounds[round].ants[id].deg = 0;
	    }
	    else {
		if (round > 0 && data.rounds[round-1].ants[id] != null)
		    data.rounds[round].ants[id].deg = data.rounds[round-1].ants[id].deg;
		else
		    data.rounds[round].ants[id].deg = 0;
	    }
	}
    }
    return true;
}


// Initializing the game.
function initGame (raw_data) {
    document.getElementById("loadingdiv").style.display = "";

    // TODO: Next two calls could run concurrently.
    if (parseData(raw_data) === false) return;
    preloadImages();

    // Prepare state variables.
    gamePaused  = false;
    gamePreview = true;

    // Canvas element.
    canvas  = document.getElementById('myCanvas');
    context = canvas.getContext("2d");

    // Prepare the slider.
    $("#slider").slider({
	slide: function(event, ui) {
	    var value = $("#slider").slider( "option", "value" );
	    curRound = value;
	    frames = 0;
	    gamePaused  = true;
	    gamePreview = true;
	}
    });
    $("#slider").width(600);
    $("#slider").slider("option", {min: 0, max: data.num_rounds});

    // Set the listerners for interaction.
    document.addEventListener('mousewheel', onDocumentMouseWheel, false);
    document.addEventListener('keydown',    onDocumentKeyDown,    false);
    document.addEventListener('keyup',      onDocumentKeyUp,      false);

    window.addEventListener('resize', onWindowResize, false);
    onWindowResize();

    document.getElementById("loadingdiv").style.display = "none";
    document.getElementById("gamediv"   ).style.display = "";

    mainloop();
}


function preloadImages () {
    data.img = new Object();


    data.img.water = new Array();
    for (var k = 0; k < 8; ++k) {
	data.img.water[k] = new Image();
	data.img.water[k].src = "img/water." + dir[k] + ".png";
    }
    data.img.water[8] = new Image();
    data.img.water[8].src = "img/water.png";

    
    data.img.soldier = new Array();
    data.img.worker  = new Array();
    data.img.queen   = new Array();
    for (var pl = 0; pl < 4; ++pl) {
	data.img.soldier[pl] = new Array();
	for (var k = 0; k < 4; ++k) {
	    data.img.soldier[pl][k] = new Image();
	    data.img.soldier[pl][k].src = "img/s" + k + "-" + player_colors[pl] + ".png";
	}
	data.img.worker [pl] = new Array();
	for (var k = 0; k < 4; ++k) {
	    data.img.worker [pl][k] = new Image();
	    data.img.worker [pl][k].src = "img/w" + k + "-" + player_colors[pl] + ".png";
	}
	data.img.queen  [pl] = new Array();
	for (var k = 0; k < 4; ++k) {
	    data.img.queen  [pl][k] = new Image();
	    data.img.queen  [pl][k].src = "img/q" + k + "-" + player_colors[pl] + ".png";
	}
    }
    data.img.bread = new Image(); data.img.bread.src = "img/" + "bread.png";
    data.img.leaf  = new Image(); data.img.leaf .src = "img/" +  "leaf.png";
    data.img.seed  = new Image(); data.img.seed .src = "img/" +  "seed.png";
}


// *********************************************************************
// Main loop functions
// *********************************************************************

function writeGameState () {

    // Write round.
    $("#round").html("Round: " + curRound);

    // Update scoreboard.
    var scoreboard = "";
    for (var i = 0; i < data.num_players; ++i) {
	scoreboard += "<span class='score'>"
	    + "<div style='display:inline-block; margin-top: 5px; width:20px; height:20px; background-color:#" + player_colors[i] + "'></div>"
	    + "<div style='display:inline-block; vertical-align: middle; margin-bottom: 7px; margin-left:8px;'>" + data.names[i] + "</div>"
	    + "<br/>"
	    + "<div style='margin-left: 3px;'>"
	    + "<div style='padding:2px;'>Carbo: " + data.rounds[curRound].carbo[i] + "</div>"
	    + "<div style='padding:2px;'>Prote: " + data.rounds[curRound].prote[i] + "</div>"
	    + "<div style='padding:2px;'>Lipid: " + data.rounds[curRound].lipid[i] + "</div>"
	    + (data.secgame ? "<div style='padding:2px;'>CPU: " + data.rounds[curRound].cpu[i] + "</div>" : "")
	    + "</div>"
	    + "</span><br/><br/>";
    }
    $("#scores").html(scoreboard);

    var order = [0, 1, 2, 3];
    for (var i = 0; i < 3; ++i) {
	for (var j = i + 1; j < 4; ++j) {
	    if (data.rounds[curRound].score[order[i]] < data.rounds[curRound].score[order[j]]) {
		var k = order[i];
		order[i] = order[j];
		order[j] = k;
	    }
	}
    }

    var totalboard = "";
    for (var i = 0; i < data.num_players; ++i) {
	totalboard += "<span class='total'>"
	    + "<div style='display:inline-block; margin-top: 5px; width:20px; height:20px; background-color:#" + player_colors[order[i]] + "'></div>"
	    + "<div style='display:inline-block; vertical-align: middle; margin-bottom: 7px; margin-left:8px;'>"
	    + data.rounds[curRound].score[order[i]] + "</div>"
	    + "</span><br/><br/>";
    }
    $("#totals").html(totalboard);
}


function drawGame () {

    // Boundary check.
    if (curRound < 0) curRound = 0;
    if (curRound >= data.num_rounds) curRound = data.num_rounds;

    // Outer Rectangle.
    context.fillStyle = "#" + grid_color;
    context.fillRect(0, 0, tileSize*data.cols, tileSize*data.rows);

    // Draw maze.
    drawRivers();
    for (var i = 0; i < data.rows; ++i)
	for (var j = 0; j < data.cols; ++j)
	    drawCell(i, j);

    // Draw ants.
    context.lineWidth = unitLineWidth;
    for (var k in data.rounds[curRound].ants) {
	var a = data.rounds[curRound].ants[k];
	var pl = a.player;
	context.strokeStyle = "#" + player_colors[pl];
	context.fillStyle   = "#" + player_colors[pl];
	var i = a.i;
	var j = a.j;
	var dir = a.dir;
	var deg = a.deg;
	var mov = false;

	if (gameAnim && a.c_type == 'm') {
	    if      (frames >= 3*frames_per_round/4) {
		if      (dir == 'd') i += 0.75;
		else if (dir == 'r') j += 0.75;
		else if (dir == 'u') i -= 0.75;
		else if (dir == 'l') j -= 0.75;
	    }
	    else if (frames >= 2*frames_per_round/4) {
		if      (dir == 'd') i += 0.5;
		else if (dir == 'r') j += 0.5;
		else if (dir == 'u') i -= 0.5;
		else if (dir == 'l') j -= 0.5;
	    }
	    else if (frames >= 1*frames_per_round/4) {
		if      (dir == 'd') i += 0.25;
		else if (dir == 'r') j += 0.25;
		else if (dir == 'u') i -= 0.25;
		else if (dir == 'l') j -= 0.25;
	    }

	    if (curRound > 0 && data.rounds[curRound-1].ants[k] != null) {
		var pdeg = data.rounds[curRound-1].ants[k].deg;
		var ndeg = data.rounds[curRound  ].ants[k].deg;
		var lim = frames_per_round/2;
		if (frames <= lim) {
		    if      (ndeg - pdeg < -180) ndeg += 360;
		    else if (ndeg - pdeg >  180) pdeg += 360;
		    deg = pdeg + (frames / lim) * (ndeg - pdeg);
		}
	    }
	    if (dir != '_') mov = true;
	}
	if      (a.type == 'w') drawWorker (i, j, pl, deg, mov, a);
	else if (a.type == 's') drawSoldier(i, j, pl, deg, mov, a);
	else                    drawQueen  (i, j, pl, deg, mov, a);
    }
}


function drawCell (i, j) {
    var cell = data.rounds[curRound].rows[i][j];
    if (cell == 'W') {
	// context.fillStyle = "#" + water_color;
	// context.fillRect(j*tileSize, i*tileSize, tileSize, tileSize);
    }
    else {
	if      (cell == 'B') context.drawImage( data.img.bread, j*tileSize, i*tileSize, tileSize, tileSize);
	else if (cell == 'L') context.drawImage( data.img.leaf,  j*tileSize, i*tileSize, tileSize, tileSize);
	else if (cell == 'S') context.drawImage( data.img.seed,  j*tileSize, i*tileSize, tileSize, tileSize);
    }
}


function drawWorker (i, j, pl, deg, mov, a) {

    var ctx = canvas.getContext('2d');
    var img = data.img.worker[pl][ mov ? (int(frames/4)) % 4 : 0];
    ctx.save();
    ctx.translate((j + 0.5)*tileSize, (i + 0.5)*tileSize); // put the origen on the center of the cell
    ctx.rotate(deg * Math.PI / 180);
    ctx.drawImage(img, -0.5*tileSize, -0.5*tileSize, tileSize, tileSize);
    ctx.restore();

    if (a.bonus != 'n') {
	ctx.beginPath();
	ctx.strokeStyle = "#" + bonus_colors[a.bonus];
	ctx.lineWidth = 2;
	ctx.arc((j + 0.5)*tileSize, (i + 0.5)*tileSize, tileSize/2, 0, Math.PI*2);
	ctx.closePath();
	ctx.stroke();
    }

    // Alternative representation.
    // var size = unitSize * tileSize;
    // var offset = (tileSize - size) / 2;
    // context.fillRect(j*tileSize + offset + 0.1*size, i*tileSize + offset + 0.1*size, 0.8*size, 0.8*size);
}


function drawSoldier (i, j, pl, deg, mov, a) {

    var ctx = canvas.getContext('2d');
    var img = data.img.soldier[pl][ mov ? int(frames/4) % 4 : 0];
    ctx.save();
    ctx.translate((j + 0.5)*tileSize, (i + 0.5)*tileSize); // put the origen on the center of the cell
    ctx.rotate(deg * Math.PI / 180);
    ctx.drawImage(img, -0.5*tileSize, -0.5*tileSize, tileSize, tileSize);
    ctx.restore();

    // Alternative representation.
    // var size = unitSize * tileSize * 0.4;
    // var offset = (tileSize - size) / 2;
    // context.beginPath();
    // context.arc(j*tileSize + size/2 + offset, i*tileSize + size/2 + offset, size/2, 0, Math.PI*2, false);
    // context.fill();
    // context.stroke();
}


function drawQueen (i, j, pl, deg, mov, a) {

    var ctx = canvas.getContext('2d');
    var img = data.img.queen[pl][ mov ? int(frames/4) % 4 : 0];
    ctx.save();
    ctx.translate((j + 0.5)*tileSize, (i + 0.5)*tileSize); // put the origen on the center of the cell
    ctx.rotate(deg * Math.PI / 180);
    ctx.drawImage(img, -0.5*tileSize, -0.5*tileSize, tileSize, tileSize);
    ctx.restore();

    // Alternative representation.
    // var size = unitSize * tileSize * 0.6;
    // var offset = (tileSize - size) / 2;
    // context.beginPath();
    // context.arc(j*tileSize + size/2 + offset, i*tileSize + size/2 + offset, size/2, 0, Math.PI*2, false);
    // context.fill();
    // context.stroke();
    // context.beginPath();
    // context.moveTo(j*tileSize + offset - 0.4*size, i*tileSize + offset - 0.4*size);
    // context.lineTo(j*tileSize + offset + 1.4*size, i*tileSize + offset + 1.4*size);
    // context.stroke();
    // context.beginPath();
    // context.moveTo(j*tileSize + offset + 1.4*size, i*tileSize + offset - 0.4*size);
    // context.lineTo(j*tileSize + offset - 0.4*size, i*tileSize + offset + 1.4*size);
    // context.stroke();
}


function direction(i1, j1, i2, j2) {
    for (var d = 0; d < 8; ++d) {
	if (i1 + diri[d] == i2 && j1 + dirj[d] == j2)
	    return d;
    }
    return -1;
}


function drawRivers() {
    for (var k = 0; k < data.rivers.length; ++k) {
	drawRiver(data.rivers[k]);
    }
}


function drawRiver(r) {
    var ctx = canvas.getContext('2d');
    for (var k = 0; k < r.length; ++k) {

	var img = data.img.water[8]; // round at the middle, in case it is isolated.
	ctx.drawImage(img, (r[k].j - 0.1)*tileSize, (r[k].i - 0.1)*tileSize, 1.2*tileSize, 1.2*tileSize);
	
	if (k-1 >= 0) {
	    var dpre = direction(r[k].i, r[k].j, r[k-1].i, r[k-1].j);
	    if (dpre == -1) {
		alert("could not find direction with "
		      + "(" + r[k].i + ", " + r[k].j + ")"
		      + " and "
		      + "(" + r[k-1].i + ", " + r[k-1].j + ")"
		     );
		return;
	    }
	    var img = data.img.water[dpre];
	    ctx.drawImage(img, (r[k].j - 0.1)*tileSize, (r[k].i - 0.1)*tileSize, 1.2*tileSize, 1.2*tileSize);
	}
	if (k+1 < r.length) {
	    var dpos = direction(r[k].i, r[k].j, r[k+1].i, r[k+1].j);
	    if (dpos == -1) {
		alert("could not find direction with "
		      + "(" + r[k].i + ", " + r[k].j + ")"
		      + " and "
		      + "(" + r[k+1].i + ", " + r[k+1].j + ")"
		     );
		return;
	    }
	    var img = data.img.water[dpos];
	    ctx.drawImage(img, r[k].j*tileSize, r[k].i*tileSize, tileSize, tileSize);
	}
    }
}



// *********************************************************************
// Button events
// *********************************************************************

function playButton () {
    gamePaused = false;
}


function pauseButton () {
    gamePaused = true;
    gamePreview = true; // To call render again.
    frames = 0;
}


function startButton () {
    gamePaused = true;
    gamePreview = true;
    frames = 0;
    curRound = 0;
}


function endButton () {
    gamePreview = true;
    frames = 0;
    curRound = data.num_rounds;
}


function animButton () {
    gameAnim = !gameAnim;
}


function closeButton () {
    window.close();
}


function helpButton () {
    help();
}


// *********************************************************************
// Keyboard and Mouse events
// *********************************************************************

function onDocumentMouseWheel (event) {
}


function onDocumentKeyDown (event) {
}


function onDocumentKeyUp (event) {
    // http://www.webonweboff.com/tips/js/event_key_codes.aspx
    switch (event.keyCode) {
    case 36: // Start.
	gamePreview = true;
	curRound = 0;
	frames = 0;
	break;

    case 35: // End.
	gamePreview = true;
	curRound = data.num_rounds;
	frames = 0;
	break;

    case 33: // PageDown.
	gamePreview = true;
	curRound -= 10;
	frames = 0;
	break;

    case 34: // PageUp.
	gamePreview = true;
	curRound += 10;
	frames = 0;
	break;

    case 38: // ArrowUp.
    case 37: // ArrowLeft.
	gamePaused= true;
	gamePreview = true;
	--curRound;
	frames = 0;
	break;

    case 40: // ArrowDown.
    case 39: // ArrowRight.
	gamePaused = true;
	gamePreview = true;
	++curRound;
	frames = 0;
	break;

    case 32: // Space.
	if (gamePaused) playButton();
	else pauseButton();
	break;

    case 72: // "h"
	helpButton();
	break;

    default:
	// $("#debug").html(event.keyCode);
	break;
    }
}


function onWindowResize (event) {
    // Constants.
    var header_height = 140; // 150;
    var canvas_margin = 0; // 20;

    // Set canvas size.
    var size = Math.min(document.body.offsetWidth, document.body.offsetHeight - header_height) - canvas_margin*2;

    canvas.width  = size;
    canvas.height = size;

    var max_dimension = Math.max(data.cols,data.rows);
    tileSize = size / max_dimension;

    drawGame();
}


function help () {
    // Opens a new popup with the help page.
    var win = window.open('help.html', 'name', 'height=400, width=300');
    if (window.focus) win.focus();
    return false;
}


// *********************************************************************
// This function is called periodically.
// *********************************************************************

function mainloop () {
    // Configure buttons.
    if (gamePaused) {
	$("#but_play").show();
	$("#but_pause").hide();
    }
    else {
	$("#but_play").hide();
	$("#but_pause").show();
    }

    if (curRound < 0) curRound = 0;

    if (curRound > data.num_rounds) {
	curRound = data.num_rounds;
	gamePaused = true;
	frames = 0;
    }

    if (!gamePaused || gamePreview) {
	$("#slider").slider("option", "value", curRound);
	drawGame();
	writeGameState();

	if (gamePreview) {
	    frames = 0;
	    gamePreview = false;
	}
	else {
	    ++frames;
	    if (frames == frames_per_round) {
		frames = 0;
		curRound += gameDirection;
	    }
	}
    }

    // Periodically call mainloop.
    var frame_time = 1000/speed;
    setTimeout(mainloop, frame_time);
}


// *********************************************************************
// Main function, it is called when the document is ready.
// *********************************************************************

function init () {
    // Get url parameters.
    var game;
    if (getURLParameter("sub") != null) {
	var domain = window.location.protocol + "//" + window.location.host;
	if (getURLParameter("nbr") != null)
	    game = domain + "/?cmd=lliuraments&sub=" + getURLParameter("sub") + "&nbr=" + getURLParameter("nbr") + "&download=partida";
	else
	    game = domain + "/?cmd=partida&sub=" + getURLParameter("sub") + "&download=partida";
    }
    else game = getURLParameter("game");

    if (game == null || game == "") {
	// Ask the user for a game input.
	var inputdiv = document.getElementById('inputdiv')
	inputdiv.style.display = "";
	document.getElementById('file').addEventListener('change', function(evt) {
	    //http://www.html5rocks.com/en/tutorials/file/dndfiles/
	    var file = evt.target.files[0];
	    var reader = new FileReader();
	    reader.readAsText(file);
	    reader.onloadend = function(evt) {
		if (evt.target.readyState != FileReader.DONE) alert("Error accessing file.");
		else { // DONE == 2.
		    inputdiv.style.display = "none";
		    document.getElementById("loadingdiv").style.display = "";
		    initGame(reader.result);
		}
	    };
	}, false);
    }
    else {
	document.getElementById("loadingdiv").style.display = "";
	// Load the given game.
	loadFile(game, initGame);
    }
}

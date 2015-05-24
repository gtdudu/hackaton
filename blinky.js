var Myo = require('myo');
var myMyo = Myo.create();
var tmpY = 0;
var tmpZ = 0;
var tmp = -1;
var fw = 0;

myMyo.on('connected', function () {
	myMyo.setLockingPolicy('none');
});

myMyo.on('orientation', function(data){

	if (tmp > 0)
	{
		console.log(tmp);
	}
	else if (tmp == -1)
		tmpY = data.y;

	if (data.y < (tmpY - 0.20))
	{
		if (fw == 0)
			tmp = 6;
		if (fw == 1)
			tmp = 3;
	}
	else if (data.y > (tmpY + 0.20))
	{
		if (fw == 0)
			tmp = 5;
		if (fw == 1)
			tmp = 4;
	}
});

myMyo.on('pose', function(pose_name, edge){

	if(pose_name == 'double_tap' && edge)
	{
		if (fw == 1)
			fw = 0;
		else
			fw = 1;
		tmp = -1;
	}
	else if(pose_name == 'fist' && edge)
	{
		tmp = 7;
		console.log("7");
	}
	else if(pose_name == 'wave_out' && edge)
	{
		angle = 0;
		tmp = 2;
		console.log('2');
	}
	else if(pose_name == 'wave_in' && edge)
	{
		tmp = 1;
		console.log('1');
	}
	else
		tmp = 0;
});

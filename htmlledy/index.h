const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
	.przycisk  {
    	background-color: rgb(200, 200, 200);
        color:white;
        border-radius:50px;
        width:100px;
        height:34px;
        margin-bottom: 20px;
    }
    
    .led {
    	background-color: red;
        color:white;
        border-radius:20px;
        width:20px;
        height:20px;
        display: inline-block;
    }
</style>
</head>
<body>

<h2 class="u-text u-text-1">Ledy</h2>
<p class="u-text u-text-2">Kliknij w przykladowy przycisk aby zobaczyc co robi</p>
	<button id="1" class="przycisk">Brama</button><br />
	<button id="1" class="przycisk">Swiatlo 1</button><span class="led"></span><br />
	<button id="1" class="przycisk">Swiatlo 2</button><span class="led"></span> 

</body>
</html> 
)=====";

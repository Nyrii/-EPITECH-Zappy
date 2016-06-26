<!doctype html>
<html>
  <head>
  	<title>Zappy</title>
  	<meta charset="utf-8">
    <link rel="stylesheet" type="text/css" href="assets/css/main.css">
  </head>
  <body>
    <div id="gui">
      <form id="connexion-form" method="post">
        <input type="text" name="ip" placeholder="192.168.140.2"/>
        <input type="text" name="port" placeholder="4242"/>
        <select name="theme" size="1">
          <option name="grass" value="grass">Grass</option>
          <option name="desert" value="desert">Desert</option>
        </select>
        <input id="btn-connect" type="submit" value="Connect">
      </form>
    </div>
    <div id="container"></div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.0.0/jquery.min.js"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/threejs/r76/three.min.js"></script>
    <script src="js/OrbitControls.js" type="text/javascript"></script>
    <script src="js/Stats.js" type="text/javascript"></script>
    <script src="js/OBJLoader.js" type="text/javascript"></script>
    <script src="js/scene.js" type="text/javascript"></script>
    <script type="text/javascript">
      $('#connexion-form').on('submit', function (e) {
        e.preventDefault();
        $.ajax({
            type: 'POST',
            url: 'connect.php',
            data: $("#connexion-form").serialize(),
            success: function (data) {
              if (data == "KO")
                alert("Unable to connect");
              else {
                var obj = $.parseJSON(data);
                scene(obj.size_x, obj.size_y, obj.theme);
              }
            },
            error: function (data) {
              console.log("Unable to call PHP script.");
            }
          });
          $("#connexion-form").css("display", "none");
      });
    </script>
  </body>
</html>

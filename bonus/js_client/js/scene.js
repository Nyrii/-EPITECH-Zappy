var camera, scene, renderer, controls, stats;
var geometry, material, mesh;
var container = document.getElementById('container');
var bs = 64;

function scene(x, z, theme) {
  init(x, z, theme);
  for (i = 0; i < x * z; i++) {
    drawRessource();
  }
  drawPlayers();
  animate();
}

function nbPlayers() {
  return $.ajax({
      type: 'GET',
      url: 'nbPlayers.php',
      success: function (data) {
      },
      error: function (data) {
        console.log("Unable to call PHP script.");
      }
    });
}

function drawPlayers() {
  var nb = nbPlayers();
  console.log(nb);
  for (i = nb; i > 0; i--) {
    $.ajax({
      type: 'GET',
      url: 'getPlayers.php',
      success: function (data) {
        var player = $.parseJSON(data);
        var geometry = new THREE.BoxGeometry(20, 20, 20);
        var material = new THREE.MeshBasicMaterial({color: 0x926239}); //brown
        var cube = new THREE.Mesh(geometry, material);
        cube.position.y = 70;
        cube.position.x = player.X;
        cube.position.z = player.Z;
        cube.scale = 200;
        scene.add(cube);
      },
      error: function (data) {
        console.log("Unable to call PHP script.");
      }
    });
  }
}

function getTeams() {
  return $.ajax({
      type: 'GET',
      url: 'getTeams.php',
      success: function (data) {
      },
      error: function (data) {
        console.log("Unable to call PHP script.");
      }
    });
}

function shuffle(o) {
    for(var j, x, i = o.length; i; j = parseInt(Math.random() * i), x = o[--i], o[i] = o[j], o[j] = x);
    return o;
};

function getCoord(obj, pos) {
  var coord = new Object();
  switch (pos) {
    case 1:
      coord.oneX = obj.X * bs;
      coord.oneZ = obj.Z * bs;
      return (coord);
      break;
    case 2:
      coord.oneX = obj.X * bs + bs / 3;
      coord.oneZ = obj.Z * bs;
      return (coord);
      break;
    case 3:
      coord.oneX = obj.X * bs + bs * (2 / 3);
      coord.oneZ = obj.Z * bs;
      return (coord);
      break;
    case 4:
      coord.oneX = obj.X * bs;
      coord.oneZ = obj.Z * bs + bs / 3;
      return (coord);
      break;
    case 5:
      coord.oneX = obj.X * bs + bs / 3;
      coord.oneZ = obj.Z * bs + bs / 3;
      return (coord);
      break;
    case 6:
      coord.oneX = obj.X * bs + bs * (2 / 3);
      coord.oneZ = obj.Z * bs + bs / 3;
      return (coord);
      break;
    case 7:
      coord.oneX = obj.X * bs;
      coord.oneZ = obj.Z * bs + bs * (2 / 3);
      return (coord);
      break;
    case 8:
      coord.oneX = obj.X * bs + bs / 3;
      coord.oneZ = obj.Z * bs + bs * (2 / 3);
      return (coord);
      break;
    case 9:
      coord.oneX = obj.X * bs + bs * (2 / 3);
      coord.oneZ = obj.Z * bs + bs * (2 / 3);
      return (coord);
      break;
  }
}

function rotate(obj) {
  obj.rotation.x += 0.01
  render();
  rotate(obj);
}

function drawFood(obj, pos) {
  if (obj.food <= 0)
    return;

  // POMME OK, MAIS TROP DE MESH
  // instantiate a loader
  var loader = new THREE.ObjectLoader();
  // load a resource
  loader.load(
  	// resource URL
  	'../assets/obj/pomme.json',
  	// Function when resource is loaded
  	function (pomme) {
      pomme.position.y = 70;
      var coord = new Object();
      coord = getCoord(obj, pos);
      pomme.position.x = coord.oneX - 20;
      pomme.position.z = coord.oneZ - 20;
      pomme.scale = 300;
  		scene.add(pomme);
  	}
  );

  // var geometry = new THREE.SphereGeometry(10, 32, 32);
  // var material = new THREE.MeshBasicMaterial({color: 0xb93939}); //red
  // var sphere = new THREE.Mesh( geometry, material );
  // sphere.position.y = 70;
  // var coord = new Object();
  // coord = getCoord(obj, pos);
  // sphere.position.x = coord.oneX - 20;
  // sphere.position.z = coord.oneZ - 20;
  // scene.add(sphere);
}

function drawLinemate(obj, pos) {
  // instantiate a loader
  var loader = new THREE.ObjectLoader();
  // load a resource
  loader.load(
  	// resource URL
  	'../assets/obj/diamond.json',
  	// Function when resource is loaded
  	function (caillou) {
      caillou.position.y = 70;
      var coord = new Object();
      coord = getCoord(obj, pos);
      caillou.position.x = coord.oneX - 20;
      caillou.position.z = coord.oneZ - 20;
      caillou.scale = 300;
  		scene.add(caillou);
  	}
  );
}

function drawDeraumere(obj, pos) {
  if (obj.deraumere <= 0)
    return;
  var geometry = new THREE.SphereGeometry(10, 32, 32);
  var material = new THREE.MeshBasicMaterial({color: 0x15d466}); //green
  var sphere = new THREE.Mesh( geometry, material );
  sphere.position.y = 70;
  var coord = new Object();
  coord = getCoord(obj, pos);
  sphere.position.x = coord.oneX - 20;
  sphere.position.z = coord.oneZ - 20;
  scene.add(sphere);
}

function drawSibur(obj, pos) {
  if (obj.sibur <= 0)
    return;
  var geometry = new THREE.SphereGeometry(10, 32, 32);
  var material = new THREE.MeshBasicMaterial({color: 0xe1f21d}); //yellow
  var sphere = new THREE.Mesh( geometry, material );
  sphere.position.y = 70;
  var coord = new Object();
  coord = getCoord(obj, pos);
  sphere.position.x = coord.oneX - 20;
  sphere.position.z = coord.oneZ - 20;
  scene.add(sphere);
}

function drawMendiane(obj, pos) {
  if (obj.mendiane <= 0)
    return;
  var geometry = new THREE.SphereGeometry(10, 32, 32);
  var material = new THREE.MeshBasicMaterial({color: 0xf29b1d}); //orange
  var sphere = new THREE.Mesh( geometry, material );
  sphere.position.y = 70;
  var coord = new Object();
  coord = getCoord(obj, pos);
  sphere.position.x = coord.oneX - 20;
  sphere.position.z = coord.oneZ - 20;
  scene.add(sphere);
}

function drawPhiras(obj, pos) {
  if (obj.phiras <= 0)
    return;
  var geometry = new THREE.SphereGeometry(10, 32, 32);
  var material = new THREE.MeshBasicMaterial({color: 0xc81df2}); //magenta
  var sphere = new THREE.Mesh( geometry, material );
  sphere.position.y = 70;
  var coord = new Object();
  coord = getCoord(obj, pos);
  sphere.position.x = coord.oneX - 20;
  sphere.position.z = coord.oneZ - 20;
  scene.add(sphere);
}

function drawThystame(obj, pos) {
  if (obj.thystame <= 0)
    return;
  var geometry = new THREE.SphereGeometry(10, 32, 32);
  var material = new THREE.MeshBasicMaterial({color: 0x35d7b7}); //cyan
  var sphere = new THREE.Mesh( geometry, material );
  sphere.position.y = 70;
  var coord = new Object();
  coord = getCoord(obj, pos);
  sphere.position.x = coord.oneX - 20;
  sphere.position.z = coord.oneZ - 20;
  scene.add(sphere);
}

function drawRessource() {
  $.ajax({
      type: 'GET',
      url: 'readMap.php',
      success: function (data) {
        var obj = $.parseJSON(data);
        var numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9];
        var pos = shuffle(numbers);
        drawFood(obj, pos[0]);
        drawLinemate(obj, pos[1]);
        drawDeraumere(obj, pos[2]);
        drawSibur(obj, pos[3]);
        drawMendiane(obj, pos[4]);
        drawPhiras(obj, pos[5]);
        drawThystame(obj, pos[6]);
      },
      error: function (data) {
        console.log("Unable to call PHP script.");
      }
    });
}

function init(x, z, theme) {
    var maxX = x * bs;
    var maxZ = z * bs;

    stats = new Stats();
    stats.showPanel(0); // 0: fps, 1: ms, 2: mb, 3+: custom
    container.appendChild(stats.dom);

    camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 1, 10000);
    camera.position.z = maxZ + maxX;

    scene = new THREE.Scene();

    var plan = new THREE.Geometry();
    var materials = [];
    for (z = 0; z < maxZ; z += bs) {
      for (x = 0; x < maxX; x += bs) {
        for (var k = 0; k < 6; k++) {
          var img = new Image();
          img.src = '../assets/textures/plan-' + theme + '-' + k + '.jpg';
          var tex = new THREE.Texture(img);
          img.tex = tex;
          img.onload = function() {
              this.tex.needsUpdate = true;
          };
          var mat = new THREE.MeshBasicMaterial({color: 0xffffff, map: tex});
          materials.push(mat);
        }
        var cubeGeo = new THREE.CubeGeometry(bs, bs * 2, bs, 1, 1, 1);
        var cube = new THREE.Mesh(cubeGeo, new THREE.MeshFaceMaterial(materials));
        cube.position.x = x;
        cube.position.z = z;
        scene.add(cube);
      }
    }

    var ambientLight = new THREE.AmbientLight(0xcccccc);
    scene.add(ambientLight);

    renderer = new THREE.WebGLRenderer();
    renderer.setSize(window.innerWidth, window.innerHeight);

    container.appendChild(renderer.domElement);

    controls = new THREE.OrbitControls(camera, renderer.domElement);

		scene.rotation.x = 0.75;
    scene.rotation.y = 0.50;

    render();
}

function animate() {
  stats.begin();
	controls.update();
	render();
  stats.end();
  requestAnimationFrame(animate);
}

function render() {
	renderer.render(scene, camera);
}

document.addEventListener("DOMContentLoaded", function(event){

  var body = document.body;
  var r = document.querySelector("#r");
  var g = document.querySelector("#g");
  var b = document.querySelector("#b");
  var r_out = document.querySelector("#r_out");
  var g_out = document.querySelector("#g_out");
  var b_out = document.querySelector("#b_out");
  var sample = document.querySelector("#sample");




  function pad(n){
    return (n.length<2) ? "0"+n : n;
  }

  r.addEventListener('change', function() {
    var r_hex = parseInt(parseFloat(r.value, 10) / 1023 * 255).toString(16);
    var g_hex = parseInt(parseFloat(g.value, 10) / 1023 * 255).toString(16);
    var b_hex = parseInt(parseFloat(b.value, 10) / 1023 * 255).toString(16);
    var hex = "#" + pad(r_hex) + pad(g_hex) + pad(b_hex);

    sample.style.backgroundColor = hex;
    console.log(hex);
    r_out.value = r.value;
  }, false);

  g.addEventListener('change', function() {
    var r_hex = parseInt(parseFloat(r.value, 10) / 1023 * 255).toString(16);
    var g_hex = parseInt(parseFloat(g.value, 10) / 1023 * 255).toString(16);
    var b_hex = parseInt(parseFloat(b.value, 10) / 1023 * 255).toString(16);
    var hex = "#" + pad(r_hex) + pad(g_hex) + pad(b_hex);

    sample.style.backgroundColor = hex;
    console.log(hex)
    g_out.value = g.value;
  }, false);

  b.addEventListener('change', function() {
    var r_hex = parseInt(parseFloat(r.value, 10) / 1023 * 255).toString(16);
    var g_hex = parseInt(parseFloat(g.value, 10) / 1023 * 255).toString(16);
    var b_hex = parseInt(parseFloat(b.value, 10) / 1023 * 255).toString(16);
    var hex = "#" + pad(r_hex) + pad(g_hex) + pad(b_hex);

    sample.style.backgroundColor = hex;
    console.log(hex)
    b_out.value = b.value;
  }, false);

});

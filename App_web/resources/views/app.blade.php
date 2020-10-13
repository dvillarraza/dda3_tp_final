<!doctype html>
<html lang="{{ str_replace('_', '-', app()->getLocale()) }}">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="csrf-token" value="{{ csrf_token() }}"/>
    <title>Sistema de Monitoreo de Dispositivos</title>
    <link href="https://fonts.googleapis.com/css?family=Nunito:200,600" rel="stylesheet" type="text/css">
    <link href="{{ mix('css/app.css') }}" type="text/css" rel="stylesheet"/>
</head>

<body>
<div id="app">
</div>
<script src="{{ mix('js/app.js') }}" type="text/javascript"></script>
</body>

<footer>
  <div class="container">
    <nav class="navbar navbar-expand-lg navbar-light bg-light">
        <div class="collapse navbar-collapse">
            <div class="navbar-nav">
              <h5 class="white-text">FIUBA -</h5>
              <div class="grey-text text-lighten-4">Especializacion IoT - Desarrollo de Aplicaciones III</div>
            </div>
        </div>
        <div class="footer-copyright">
          <div class="container">
            © 2020
          </div>
        </div>
    </nav>
  <div class="container">
</footer>

</html>

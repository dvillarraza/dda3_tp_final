<template>
    <div class="container">
        <div class="text-center" style="margin: 20px 0px 20px 0px;">
            <span class="text-secondary">Sistema de Monitoreo de Dispositivos</span>
        </div>

        <nav class="navbar navbar-expand-lg navbar-light bg-light">
            <div class="collapse navbar-collapse">
                <div class="navbar-nav">
                    <router-link to="/" class="btn btn-primary">Inicio</router-link>
                </div>
            </div>
        </nav>
        <br/>
        <router-view></router-view>
        <br/>
    </div>   
</template>

<style>
    .bg-light {
        background-color: #eae9e9 !important;
    }
    .text-secondary {
        font-size: 24px;
    }
        .text-center {
        font-size: 20px;
    }
</style>


<script>
    export default {}
</script>
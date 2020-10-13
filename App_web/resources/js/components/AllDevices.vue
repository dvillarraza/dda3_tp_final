<template>
    <div>

        <h3 class="text-center">Lista de Dispositivos</h3><br/>
        <table class="table table-bordered">
            <thead>
            <tr>
                <th>ID</th>
                <th>Device Id</th>
                <th>Nombre</th>
                <th>Ubicacion</th>
                <th>Acciones</th>
                <th>Comando Remoto</th>
                <th>Datos Historicos</th>
            </tr>
            </thead>
            <tbody>
            <tr v-for="device in devices" :key="device.id">
                <td>{{ device.id }}</td>
                <td>{{ device.device_id }}</td>
                <td>{{ device.name }}</td>
                <td>{{ device.ubication }}</td>
                <td>
                    <div class="btn-group" role="group">
                        <button class="btn btn-danger" @click="deleteDevice(device.id)">Borrar</button>
                        <router-link :to="{name: 'edit', params: { id: device.id }}" class="btn btn-primary">Editar</router-link>
                    </div>
                </td>
                <td>
                    <div class="btn-group" role="group">
                        <router-link :to="{name: 'online', params: { id: device.id }}" class="btn btn-primary">Online</router-link>
                    </div>
                </td>
                <td>
                    <div class="btn-group" role="group">
                        <router-link :to="{name: 'grafico', params: { id: device.id }}" class="btn btn-primary">Graficos</router-link>
                    </div>
                </td>
            </tr>
            </tbody>
        </table>
        <router-link to="/add" class="btn btn-primary">Agregar Dispositivo</router-link>
    </div>
</template>

<script>
    export default {
        data() {
            return {
                devices: []
            }
        },
        created() {
            axios
                .get('http://192.168.0.65:8000/api/devices')
                .then(response => {
                    this.devices = response.data;
                });
        },
        methods: {
            deleteDevice(id) {
                axios
                    .delete(`http://192.168.0.65:8000/api/device/delete/${id}`)
                    .then(response => {
                     //   console.log(response.data);
                        let i = this.devices.map(item => item.id).indexOf(id); // find index of your object
                        this.devices.splice(i, 1)
                    });
            }
        }
    }
</script>
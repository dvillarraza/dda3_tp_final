<template>
    <div>
        <h3 class="text-center">Agregar Dispositivo</h3>
        <div class="row">
            <div class="col-md-6">
                <form @submit.prevent="addDevice">
                    <div class="form-group">
                        <label>Device ID</label>
                        <input type="text" class="form-control" v-model="device.device_id">
                    </div>
                    <div class="form-group">
                        <label>Nombre</label>
                        <input type="text" class="form-control" v-model="device.name">
                    </div>
                    <div class="form-group">
                        <label>Ubicacion</label>
                        <input type="text" class="form-control" v-model="device.ubication">
                    </div>
                    <button type="submit" class="btn btn-primary">Aregar Dispositivo</button>
                </form>
            </div>
        </div>
    </div>
</template>

<script>
    export default {
        data() {
            return {
                device: {}
            }
        },
        methods: {
            addDevice() {
                axios
                    .post('http://192.168.0.65:8000/api/device/add', this.device)
                    .then(response => {
                        this.$router.push({name: 'home'});
                       // console.log(response.data);
                    })
                    .catch(error => console.log(error))
                    .finally(() => this.loading = false)
            }
        }
    }
</script>
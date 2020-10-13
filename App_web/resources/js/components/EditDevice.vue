<template>
    <div>
        <h3 class="text-center">Editar Dispositivo</h3>
        <div class="row">
            <div class="col-md-6">
                <form @submit.prevent="updateDevice">
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
                    <button type="submit" class="btn btn-primary">Actualizar Dispisitivo</button>
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
        created() {
            axios
                .get(`http://192.168.0.65:8000/api/device/edit/${this.$route.params.id}`)
                .then((response) => {
                    this.device = response.data;
                });
        },
        methods: {
            updateDevice() {
                axios
                    .post(`http://192.168.0.65:8000/api/device/update/${this.$route.params.id}`, this.device)
                    .then((response) => {
                        this.$router.push({name: 'home'});
                    });
            }
        }
    }
</script>
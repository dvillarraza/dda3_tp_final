<template>
  <div id="app">
    <h3 class="text-center">Gráfico Histórico del Dispositivo</h3><br/>
    <div v-if="NotData">Leyendo Datos de la Base de datos...</div>
    <div v-else>
      
      <div class="Dispositivo ID"> Dispoitivo ID: {{this.device.device_id}}</div>
      <div class="Nombre"> Nombre: {{this.device.name}}</div>
      <div class="Ubicacion"> Ubicacion: {{this.device.ubication}}</div>
      <br>
      <GChart type="LineChart" :data="chartData" :options="chartOptions" />
   </div>
  </div>
</template>

<script>
import { GChart } from "vue-google-charts";
export default {
  components: {
    GChart,
  },
  data() {
    return {
      device: {},
      NotData: true,
      // Array will be automatically processed with visualization.arrayToDataTable function
      chartData: [],
      chartOptions: {
        chart: {
          title: "Grafico Historico",
          subtitle: "Datos de dispositivo ESP32 almacenados en la base de datos",
        },
      },
    };
  },
  methods:{
      loadData() {
        axios
          .get(`http://192.168.0.65:8000/api/device/edit/${this.$route.params.id}`)
          .then((response) => {
            this.device = response.data;
            axios.get(`http://192.168.0.65:8000/api/serie/leer/${this.device.device_id}`)
                      .then((response)=>{
                       // console.log(response);
                        var data = [["Fecha", "Temperatura", "Humedad"]];
                        response.data.forEach(obj => {
                          var date = new Date(parseInt(obj.timestamp));
                          var fil = [date, parseFloat(obj.temp), parseFloat(obj.hum)];
                          data.push(fil);
                        });
                        this.chartData = data;
                        this.NotData = false;
                      });
          });
      }
  },
  created() {
      this.loadData();
  }
};
</script>

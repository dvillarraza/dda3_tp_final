<template>
  <div class="publish">
    <h3 class="text-center">Comando Remoto de Dispositivo Online</h3><br/>
    <div v-if="NotDevice">Leyendo Dispositivos...</div>
    <div v-else>
      
      <div class="Dispositivo ID"> Dispoitivo ID: {{this.device.device_id}}</div>
      <div class="Nombre"> Nombre: {{this.device.name}}</div>
      <div class="Ubicacion"> Ubicacion: {{this.device.ubication}}</div>
      <br>
      <div v-if="NotMqtt">Esperando respuesta de Dispositivo...</div>
      <div v-else>
        <div class="Temperatura"> Temperatura: {{this.temp}} °C</div>
        <div class="Humedad"> Humedad: {{this.hum}} %</div>
        <div class="Led"> Estado Led: {{this.led}}</div>
        <button @click="publish1">Prender Led</button>
        <button @click="publish2">Apagar Led</button>
      </div>
      <br>
    </div>
  </div>
</template>

<script>
export default {
  data () {
    return {
      device: {},
      topictemp: '',
      topichum: '',
      topicled: '',
      temp: '',
      hum: '',
      led:'',
      NotDevice: true,
      NotMqtt: true,
    }
  },
  created() {
      axios
          .get(`http://192.168.0.65:8000/api/device/edit/${this.$route.params.id}`)
          .then((response) => {
              this.device = response.data;
              this.topictemp = this.device.device_id + '/dht/temperature';
              this.topichum = this.device.device_id + '/dht/humidity';
              this.topicled = this.device.device_id + '/status/led';
              this.$mqtt.subscribe(this.topictemp);
              this.$mqtt.subscribe(this.topichum);
              this.$mqtt.subscribe(this.topicled);
              this.NotDevice = false;
          })
  },
  methods: {
    publish1 () {
//      console.log("Led on")
      this.$mqtt.publish(this.device.device_id + '/led', 'on')
    },
    publish2 () {
//      console.log("Led off")
      this.$mqtt.publish(this.device.device_id + '/led', 'off')
    },
  },
  mqtt: {
    '#' (data,topic) {
      if (topic == this.topictemp){
        this.NotMqtt = false;
 //       console.log("Temperatura: " + data)
        this.temp = data;
      }
      if (topic == this.topichum){
 //       console.log("Humedad: " + data)
        this.NotMqtt = false;
        this.hum = data;
      }
      if (topic == this.topicled){
 //       console.log("Humedad: " + data) 
        this.NotMqtt = false;
        if (data == 0)
          this.led = "Apagado";
        if (data == 1)
          this.led = "Encendido";
      }
    },
  }
}
</script>


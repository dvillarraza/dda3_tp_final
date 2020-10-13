/**
 * First we will load all of this project's JavaScript dependencies which
 * includes Vue and other libraries. It is a great starting point when
 * building robust, powerful web applications using Vue and Laravel.
 */

require('./bootstrap');

window.Vue = require('vue');

import App from './App.vue';
import VueRouter from 'vue-router';
import VueMqtt from 'vue-mqtt'
import {routes} from './routes';

Vue.use(VueRouter);
Vue.use(VueMqtt, 'ws://192.168.0.65:9001', {clientId: 'WebClient-' + parseInt(Math.random() * 100000)})
//Vue.config.productionTip = false

const router = new VueRouter({
    mode: 'history',
    routes: routes
});

const app = new Vue({
    el: '#app',
    router: router,
    render: h => h(App),
});

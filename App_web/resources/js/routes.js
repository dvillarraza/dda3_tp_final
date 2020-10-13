import AllDevices from './components/AllDevices.vue';
import AddDevice from './components/AddDevice.vue';
import EditDevice from './components/EditDevice.vue';
import MqttDevice from './components/MqttDevice.vue';
import LineCharts from './components/LineCharts.vue';

export const routes = [
    {
        name: 'home',
        path: '/',
        component: AllDevices
    },
    {
        name: 'add',
        path: '/add',
        component: AddDevice
    },
    {
        name: 'edit',
        path: '/edit/:id',
        component: EditDevice
    },
    {
        name: 'online',
        path: '/online/:id',
        component: MqttDevice
    },
    {
        name: 'grafico',
        path: '/grafico/:id',
        component: LineCharts
    }
];
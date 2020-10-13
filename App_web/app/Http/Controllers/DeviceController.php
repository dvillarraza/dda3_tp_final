<?php

namespace App\Http\Controllers;

use App\Models\Device;
use Illuminate\Http\Request;

class DeviceController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    //Todos los dispositivos
    public function index()
    {
        $devices = Device::all()->toArray();
        return array_reverse($devices);
    }

    // Agregar un dispositivo
    public function add(Request $request)
    {

        $device = new Device([
            'device_id' => $request->input('device_id'),
            'name' => $request->input('name'),
            'ubication' => $request->input('ubication')
        ]);
        $device->save();

        return response()->json('El dispostivo se agregó correctamente');
    }



    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
  /*  public function create()
    {
        //
    }*/

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
 /*   public function store(Request $request)
    {
        //
    }*/

    /**
     * Display the specified resource.
     *
     * @param  \App\Models\Device  $device
     * @return \Illuminate\Http\Response
     */
 /*   public function show(Device $device)
    {
        //
    }*/

    /**
     * Show the form for editing the specified resource.
     *
     * @param  \App\Models\Device  $device
     * @return \Illuminate\Http\Response
     */
    
    // Editar un dispositivo
    public function edit($id)
    {
        $device = Device::find($id);
        return response()->json($device);
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \App\Models\Device  $device
     * @return \Illuminate\Http\Response
     */
    //Actualizar un dispositivo
    public function update($id, Request $request)
    {
        $device = Device::find($id);
        $device->update($request->all());

        return response()->json('El dispostivo se actualizó correctamente');
    }

    // Borrar un dispositivo
    public function delete($id)
    {
        $device = Device::find($id);
        $device->delete();

        return response()->json('El dispositivo se borro correctamente');
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  \App\Models\Device  $device
     * @return \Illuminate\Http\Response
     */
    /*public function destroy(Device $device)
    {
        //
    }*/
}

<?php

namespace App\Http\Controllers;

use App\Models\Serie;
use Illuminate\Http\Request;

class SerieController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    //Devuelve todos los datos de las series
    public function index()
    {
        $devices = Serie::all()->toArray();
        return array_reverse($devices);
    }

    // Leer serie un dispositivo con el device_id pasado como parametro 
    public function leer($device_id)
    {
        $series = Serie::where('device_id','=',$device_id)->get();
        return response()->json($series);
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        //
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        //
    }

    /**
     * Display the specified resource.
     *
     * @param  \App\Models\serie  $serie
     * @return \Illuminate\Http\Response
     */
    public function show(serie $serie)
    {
        //
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \App\Models\serie  $serie
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, serie $serie)
    {
        //
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  \App\Models\serie  $serie
     * @return \Illuminate\Http\Response
     */
    public function destroy(serie $serie)
    {
        //
    }
}

<?php

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| API Routes
|--------------------------------------------------------------------------
|
| Here is where you can register API routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| is assigned the "api" middleware group. Enjoy building your API!
|
*/

Route::middleware('auth:api')->get('/user', function (Request $request) {
    return $request->user();
});

//Defino las rutas de los dispositivos
Route::get('devices', 'App\Http\Controllers\DeviceController@index');
Route::group(['prefix' => 'device'], function () {
    Route::post('add', 'App\Http\Controllers\DeviceController@add');
    Route::get('edit/{id}', 'App\Http\Controllers\DeviceController@edit');
    Route::post('update/{id}', 'App\Http\Controllers\DeviceController@update');
    Route::delete('delete/{id}', 'App\Http\Controllers\DeviceController@delete');
    
});

//Defino las rutas de las series 
Route::get('series', 'App\Http\Controllers\SerieController@index');
Route::group(['prefix' => 'serie'], function () {
    Route::get('leer/{id}', 'App\Http\Controllers\SerieController@leer');   
});


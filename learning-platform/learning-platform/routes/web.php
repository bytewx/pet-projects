<?php

use App\Http\Controllers\CourseController;
use App\Http\Controllers\ProfileController;
use Illuminate\Support\Facades\Route;

Route::view('/', 'welcome');

Route::middleware('auth')->group(function () {
    Route::view('/dashboard', 'dashboard')->name('dashboard');

    Route::get('/profile', [ProfileController::class, 'edit'])->name('profile.edit');
    Route::patch('/profile', [ProfileController::class, 'update'])->name('profile.update');
    Route::delete('/profile', [ProfileController::class, 'destroy'])->name('profile.destroy');

    Route::controller(CourseController::class)->group(function () {
        Route::get('/courses', 'index')->name('courses.index');
        Route::get('/courses/create', 'create')->name('courses.create');
        Route::post('/courses', 'store')->name('courses.store');
        Route::get('/courses/{course}', 'show')->name('courses.show');
        Route::get('/courses/{course}/edit', 'edit')->name('courses.edit');
        Route::put('/courses/{course}', 'update')->name('courses.update');
        Route::delete('/courses/{course}', 'destroy')->name('courses.destroy');
    });
});

require __DIR__.'/auth.php';

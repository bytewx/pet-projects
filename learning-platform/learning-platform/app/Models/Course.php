<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;

/**
 * @method static create(array $validated)
 * @property string $name
 * @property string $description
 * @property string $category
 * @property boolean $enabled
 */
class Course extends Model
{
    /**
     * The attributes that are mass assignable.
     *
     * @var list<string>
     */
    protected $fillable = [
        'name',
        'description',
        'category',
        'enabled'
    ];
}

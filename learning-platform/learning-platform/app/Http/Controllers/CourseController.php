<?php

namespace App\Http\Controllers;

use App\Http\Requests\CourseRequest;
use App\Models\Course;
use Illuminate\Http\RedirectResponse;
use Illuminate\View\View;

class CourseController extends Controller
{
    /**
     * @return View
     */
    public function index(): View
    {
        $courses = Course::all();

        return view('courses.index', compact('courses'));
    }

    /**
     * @return View
     */
    public function create(): View
    {
        return view('courses.create');
    }

    /**
     * @param CourseRequest $request
     * @return RedirectResponse
     */
    public function store(CourseRequest $request): RedirectResponse
    {
        Course::create($request->validated());

        return redirect()->route('courses.index')->with('success', 'Course created successfully.');
    }

    /**
     * @param Course $course
     * @return View
     */
    public function show(Course $course): View
    {
        return view('courses.show', compact('course'));
    }

    /**
     * @param Course $course
     * @return View
     */
    public function edit(Course $course): View
    {
        return view('courses.edit', compact('course'));
    }

    /**
     * @param CourseRequest $request
     * @param Course $course
     * @return RedirectResponse
     */
    public function update(CourseRequest $request, Course $course): RedirectResponse
    {
        $course->update($request->validated());

        return redirect()->route('courses.index')->with('success', 'Course updated successfully.');
    }

    /**
     * @param Course $course
     * @return RedirectResponse
     */
    public function destroy(Course $course): RedirectResponse
    {
        $course->delete();

        return redirect()->route('courses.index')->with('success', 'Course deleted successfully.');
    }
}

<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            {{ __('Courses') }}
        </h2>
    </x-slot>

    <div class="py-12">
        <div class="max-w-7xl mx-auto sm:px-6 lg:px-8">
            <div class="bg-white overflow-hidden shadow-sm sm:rounded-lg">
                <div class="container mx-auto p-6">
                    <h2 class="text-2xl font-bold mb-4">{{ __('All courses') }}</h2>
                    <div class="overflow-x-auto">
                        <table class="min-w-full table-auto border-collapse">
                            <thead>
                            <tr>
                                <th class="px-4 py-2 border-b text-left">Course name</th>
                                <th class="px-4 py-2 border-b text-left">Category</th>
                                <th class="px-4 py-2 border-b text-left">Enabled</th>
                                <th class="px-4 py-2 border-b text-left">Actions</th>
                            </tr>
                            </thead>
                            <tbody>
                            @foreach ($courses as $course)
                                <tr>
                                    <td class="px-4 py-2 border-b">{{ $course->name }}</td>
                                    <td class="px-4 py-2 border-b">{{ $course->category }}</td>
                                    <td class="px-4 py-2 border-b">{{ $course->enabled ? 'Yes' : 'No' }}</td>
                                    <td class="px-4 py-2 border-b">
                                        <x-primary-button>
                                            <a href="{{ route('courses.show', $course->id) }}">
                                                View
                                            </a>
                                        </x-primary-button>

                                        <x-primary-button>
                                            <a href="{{ route('courses.edit', $course->id) }}">
                                                Edit
                                            </a>
                                        </x-primary-button>

                                        <form action="{{ route('courses.destroy', $course->id) }}" method="POST" class="inline-block">
                                            @csrf
                                            @method('DELETE')

                                            <x-primary-button type="submit">
                                                Delete
                                            </x-primary-button>
                                        </form>
                                    </td>
                                </tr>
                            @endforeach
                            </tbody>
                        </table>
                    </div>
                </div>

                <div class="p-6 text-white-900">
                    <x-primary-button>
                        <a href="{{ route('courses.create') }}" class="text-white">
                            {{ __('Create new course') }}
                        </a>
                    </x-primary-button>
                </div>
            </div>
        </div>
    </div>
</x-app-layout>

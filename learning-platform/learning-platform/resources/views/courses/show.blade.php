<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            {{ __('Chosen course') }}
        </h2>
    </x-slot>

    <div class="py-12">
        <div class="max-w-7xl mx-auto sm:px-6 lg:px-8">
            <div class="bg-white overflow-hidden shadow-sm sm:rounded-lg">
                <div class="container mx-auto p-6">
                    <h2 class="text-2xl font-bold mb-4">{{ __('Course') }}</h2>
                    <div class="overflow-x-auto">
                        <h2 class="text-2xl font-bold mb-4">{{ __('Course name: ' . $course->name) }}</h2>
                        <h2 class="text-2xl font-bold mb-4">{{ __('Course description: ' . $course->description) }}</h2>
                        <h2 class="text-2xl font-bold mb-4">{{ __('Course category: ' . $course->category) }}</h2>
                        <h2 class="text-2xl font-bold mb-4">{{ __('Course enabled: ') }} {{ $course->enabled ? 'Yes' : 'No' }}</h2>
                    </div>
                </div>
            </div>
        </div>
    </div>
</x-app-layout>

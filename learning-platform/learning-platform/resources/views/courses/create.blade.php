<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            {{ __('Create course') }}
        </h2>
    </x-slot>

    <div class="py-12">
        <div class="max-w-7xl mx-auto sm:px-6 lg:px-8">
            <div class="bg-white overflow-hidden shadow-sm sm:rounded-lg">
                <form method="POST" action="{{ route('courses.store') }}">
                    @csrf

                    <div class="p-6">
                        <x-input-label for="name" :value="__('Course name')" />
                        <x-text-input id="name" class="block mt-1 w-full" type="text" name="name" :value="old('name')" autocomplete="name" />
                        <x-input-error :messages="$errors->get('name')" class="mt-2" />

                        <x-input-label for="description" :value="__('Course description')" class="mt-2" />
                        <x-text-input id="description" class="block mt-1 w-full" type="text" name="description" :value="old('description')" autocomplete="description" />
                        <x-input-error :messages="$errors->get('description')" class="mt-2" />

                        <x-input-label for="category" :value="__('Course category')" class="mt-2" />
                        <x-text-input id="category" class="block mt-1 w-full" type="text" name="category" :value="old('category')" autocomplete="category" />
                        <x-input-error :messages="$errors->get('category')" class="mt-2" />

                        <x-input-label for="enabled" :value="__('Enabled')" class="mt-2" />
                        <input type="checkbox" name="enabled" id="enabled" class="rounded border-gray-300 text-indigo-600 shadow-sm focus:ring focus:ring-indigo-200 focus:ring-opacity-50" value="1" {{ old('enabled', $course->enabled ?? false) ? 'checked' : '' }}>
                        <x-input-error :messages="$errors->get('enabled')" class="mt-2" />
                    </div>

                    <div class="p-6">
                        <x-primary-button class="text-white">
                            {{ __('Create new course') }}
                        </x-primary-button>
                    </div>
                </form>
            </div>
        </div>
    </div>
</x-app-layout>

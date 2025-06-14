document.addEventListener('DOMContentLoaded', function () {
    const navToggle = document.querySelector('.nav-toggle');
    const navLinks = document.querySelector('.nav-links');
    if (navToggle && navLinks) {
        navToggle.addEventListener('click', () => {
            navLinks.classList.toggle('open');
        });
    }

    // Simple form handler (prevents default submit)
    const form = document.querySelector('.contact-form');
    if (form) {
        form.addEventListener('submit', function (e) {
            e.preventDefault();
            alert('Thank you for contacting us!');
            form.reset();
        });
    }

    // FAQ accordion
    document.querySelectorAll('.faq-question').forEach(q => {
        q.addEventListener('click', function () {
            const item = this.parentElement;
            item.classList.toggle('open');
        });
    });

    // Gallery modal
    const galleryImages = document.querySelectorAll('.gallery-grid img');
    const galleryModal = document.getElementById('galleryModal');
    const galleryModalImg = document.getElementById('galleryModalImg');
    const galleryModalClose = document.getElementById('galleryModalClose');
    if (galleryImages.length && galleryModal && galleryModalImg && galleryModalClose) {
        galleryImages.forEach(img => {
            img.addEventListener('click', () => {
                galleryModalImg.src = img.src;
                galleryModal.classList.add('open');
            });
        });
        galleryModalClose.addEventListener('click', () => {
            galleryModal.classList.remove('open');
        });
        galleryModal.addEventListener('click', (e) => {
            if (e.target === galleryModal) galleryModal.classList.remove('open');
        });
    }

    // Team modal
    const teamMembers = document.querySelectorAll('.team-member');
    const teamModal = document.getElementById('teamModal');
    const teamModalContent = document.getElementById('teamModalContent');
    const teamModalClose = document.getElementById('teamModalClose');
    if (teamMembers.length && teamModal && teamModalContent && teamModalClose) {
        teamMembers.forEach(member => {
            member.addEventListener('click', () => {
                teamModalContent.innerHTML = member.querySelector('.team-details').innerHTML;
                teamModal.classList.add('open');
            });
        });
        teamModalClose.addEventListener('click', () => {
            teamModal.classList.remove('open');
        });
        teamModal.addEventListener('click', (e) => {
            if (e.target === teamModal) teamModal.classList.remove('open');
        });
    }
});

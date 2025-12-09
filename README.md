# 🖥️ Braian Web Admin Panel

## 📌 Descripción del proyecto
Este panel de administración es una aplicación de escritorio, diseñada para gestionar el contenido que se muestra en mi sitio web personal (*Braian Web*).
A través de una interfaz ligera y funcional, permite interactuar directamente con mi **Braian Web API**, administrando proyectos, tecnologías, imágenes e información general del portfolio sin necesidad de modificar el código del frontend.

---

## 🎯 ¿Por qué lo hice?
Creé este panel porque necesitaba una forma cómoda y profesional de modificar mi portfolio sin tener que actualizar archivos HTML/JS cada vez que quisiera agregar un nuevo proyecto o cambiar una imagen.

Además:
- Me permitió trabajar con tecnologías en las que ya tengo experiencia (**C++ y Qt**).
- Me sirvió para practicar conceptos como autenticación con JWT, manejo de networking con Qt y subida de archivos.

---

## ✨ Características actuales
- Inicio de sesión con autenticación basada en JWT.
- Gestión completa de:
  - **Tecnologías**
  - **Proyectos**
  - **Imágenes asociadas**
  - **Información del portfolio**
- Subida de archivos con *multipart/form-data*
- Uso de librerías propias:
  - **BasicRequests** 
  - **CommonUtils** 
- Persistencia local del *refresh token* mediante **QSettings**.
- Interfaz construida con **Qt Widgets**, orientada a la simplicidad y claridad.

---

## 🚀 Implementaciones futuras
Estas son mejoras planificadas para continuar ampliando el panel:

- **Renovar token automáticamente:**  
  Implementar el flujo completo de refresco automático del refresh token sin intervención del usuario.

- **Operaciones PUT para el portfolio:**  
  Permitir actualizar los datos principales del portfolio (nombre, descripción, foto, etc.) directamente desde el panel.

- **Operaciones PUT por proyecto:**  
  Implementar actualización de proyectos existentes (nombre, descripciones, imágenes, tecnologías asociadas).


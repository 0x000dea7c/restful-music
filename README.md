# restful-music

RESTful Music Playlist API. This is a C++ web application that allows a user to create, edit and delete music playlists.

The point of this project is to learn how RESTful APIs work and play around with testing libraries in C++.

# Playlist Metadata

- Title (required)
- Description

# Song Metadata

- Title (required)
- Duration (required)
- Artist (required)
- Album
- Release Date

# Endpoints

## Playlists Actions

- GET /playlists: lists user's playlists

- GET /playlist/{id}: shows playlist metadata with its songs

- POST /playlists: given a valid JSON, it creates a music playlist

- DELETE /playlists/{id}: deletes a given playlist

- PUT /playlists/{id}: update playlist metadata

## Songs Actions

- POST /playlists/{id}/songs: adds a song to a given playlist

- DELETE /playlists/{id}/songs/{id}: removes a song from a playlist

- GET /songs/search...: search a song with parameters

## Users Actions

- POST /users/register: create a user with username, password and email. Send confirmation email (events)

- POST /users/login: authenticate and return a JWT.

# Misc

- Input validation
- Error handling (400 bad request, 401 unauthorized, 404 not found)
- Unit tests for all endpoints
- Integration tests
- Functional tests?

# Dependencies

- Crow
- sqlitecpp
- boost-uuid
- sodium
- GTest

# Tasks


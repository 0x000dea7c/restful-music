include(GoogleTest)

include_directories(${COMMON_INCLUDE_DIRECTORY})

add_executable(tests
  ${SOURCE_DIRECTORY}/username.cpp
  ${SOURCE_DIRECTORY}/password.cpp
  ${SOURCE_DIRECTORY}/email.cpp
  ${SOURCE_DIRECTORY}/uuid.cpp
  ${SOURCE_DIRECTORY}/user.cpp
  ${SOURCE_DIRECTORY}/song_title.cpp
  ${SOURCE_DIRECTORY}/song_artist.cpp
  ${SOURCE_DIRECTORY}/song_album.cpp
  ${SOURCE_DIRECTORY}/song_release_date.cpp
  ${SOURCE_DIRECTORY}/song_duration.cpp
  ${SOURCE_DIRECTORY}/password_encryptor_sodium.cpp
  ${SOURCE_DIRECTORY}/database_repository_sqlite.cpp
  ${SOURCE_DIRECTORY}/user_usecase_register.cpp
  ${SOURCE_DIRECTORY}/user_usecase_login.cpp
  test_unit_username.cpp
  test_unit_password.cpp
  test_unit_email.cpp
  test_unit_song_title.cpp
  test_unit_song_artist.cpp
  test_unit_song_album.cpp
  test_unit_song_release_date.cpp
  test_unit_song_duration.cpp
  test_unit_usecase_register.cpp
  test_unit_usecase_login.cpp
  test_integration_usecase_register.cpp
  test_integration_usecase_login.cpp
  test_main.cpp)

gtest_discover_tests(tests)

target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main sodium)

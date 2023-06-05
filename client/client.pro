QT += core\
      sql \
      gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 c++14 c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
HEADERS +=  \
            helloworld.grpc.pb.h \
            helloworld.pb.h \
            coba_lagi.h  \
            mainwindow.h
          

SOURCES +=  coba_lagi.cpp \
            helloworld.grpc.pb.cc \
            helloworld.pb.cc \
            main.cpp \
            mainwindow.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../../../../../grpc/grpc/lib/ -lre2 -lcares -lcrypto  -lssl -lupb -lz \
-labsl_bad_any_cast_impl -labsl_bad_optional_access -labsl_bad_variant_access -labsl_base -labsl_city -labsl_civil_time -labsl_cord -labsl_cord_internal \
-labsl_cordz_functions -labsl_cordz_handle -labsl_cordz_info -labsl_cordz_sample_token -labsl_crc32c -labsl_crc_cord_state -labsl_crc_cpu_detect \
-labsl_crc_internal -labsl_debugging_internal -labsl_demangle_internal -labsl_die_if_null -labsl_examine_stack -labsl_exponential_biased -labsl_failure_signal_handler \
-labsl_flags -labsl_flags_commandlineflag -labsl_flags_commandlineflag_internal -labsl_flags_config -labsl_flags_internal -labsl_flags_marshalling -labsl_flags_parse \
-labsl_flags_private_handle_accessor -labsl_flags_program_name -labsl_flags_reflection -labsl_flags_usage -labsl_flags_usage_internal -labsl_graphcycles_internal \
-labsl_hash -labsl_hashtablez_sampler -labsl_int128 -labsl_leak_check -labsl_log_entry -labsl_log_flags -labsl_log_globals -labsl_log_initialize \
-labsl_log_internal_check_op -labsl_log_internal_conditions -labsl_log_internal_format -labsl_log_internal_globals -labsl_log_internal_log_sink_set \
-labsl_log_internal_message -labsl_log_severity -labsl_log_internal_proto -labsl_log_internal_nullguard \
-laddress_sorting -labsl_time_zone -labsl_time -labsl_throw_delegate -labsl_synchronization -labsl_symbolize -labsl_strings_internal -labsl_strings \
-labsl_str_format_internal -labsl_strerror -labsl_statusor -labsl_status -labsl_spinlock_wait -labsl_scoped_set_env -labsl_raw_logging_internal \
-labsl_raw_hash_set -labsl_random_seed_sequences -labsl_random_seed_gen_exception -labsl_random_internal_seed_material -labsl_random_internal_randen_slow \
-labsl_random_internal_randen_hwaes_impl -labsl_random_internal_randen_hwaes -labsl_random_internal_randen -labsl_random_internal_pool_urbg -labsl_random_internal_platform \
-labsl_random_distributions -labsl_random_internal_distribution_test_util -labsl_periodic_sampler -labsl_malloc_internal -labsl_low_level_hash -labsl_log_sink

INCLUDEPATH += $$PWD/../../../../../grpc/grpc/include
DEPENDPATH += $$PWD/../../../../../grpc/grpc/include

unix:!macx: LIBS += -L$$PWD/../../../../../../../../../usr/local/lib/ -lupb -lgrpc -lgrpc++ -lgpr -lgrpc++_alts -lgrpc_authorization_provider \
-lgrpc++_error_details -lgrpc_plugin_support -lgrpc++_reflection -lgrpc++_unsecure -lgrpc_unsecure \
-lprotobuf-lite -lprotoc -lprotobuf
INCLUDEPATH += $$PWD/../../../../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../../../../usr/local/include

FORMS += \
    mainwindow.ui

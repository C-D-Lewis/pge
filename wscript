#
# This file is the default set of rules to compile a Pebble project.
#
# Feel free to customize this to your needs.
#
top = '.'
out = 'build'


def options(ctx):
    ctx.load('pebble_sdk_lib')


def configure(ctx):
    ctx.load('pebble_sdk_lib')


def build(ctx):
    ctx.load('pebble_sdk_lib')

    cached_env = ctx.env
    for platform in ctx.env.TARGET_PLATFORMS:
        ctx.env = ctx.all_envs[platform]
        ctx.set_group(ctx.env.PLATFORM_NAME)
        lib_name = '{}/{}'.format(ctx.env.BUILD_DIR, ctx.env.PROJECT_INFO['name'])
        ctx.pbl_build(source=ctx.path.ant_glob('src/c/**/*.c'), target=lib_name, bin_type='lib')
    ctx.env = cached_env

    ctx.set_group('bundle')
    ctx.pbl_bundle(includes=ctx.path.ant_glob('include/**/*.h'),
                   js=ctx.path.ant_glob(['src/js/**/*.js', 'src/js/**/*.json']),
                   bin_type='lib')
